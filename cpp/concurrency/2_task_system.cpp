#include <vector>
#include <deque>

#include <functional>
#include <memory>
#include <new>
#include <type_traits>

#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <future>

using namespace std;

/*
NDC London 2017 Sean Parent: avoid concurrency permitives. 
use a task queue, use a task system. example: apple Grand Center Dispatch (GDC) libdispatch

std::asyn doesn't specify it's running on thread or in a thread pool.
*/
using Task = function<void()>; // keep task simple, add future outside of task system

/*For a task system, we need a queue*/
class alignas(64) notification_queue { // avoid false share
    deque<Task> q_;
    mutex mtx_;
    condition_variable cv_;
    bool done_{false};

public:
    void stop() {
        {
            lock_guard<mutex> g(mtx_);
            done_ = true;
        }
        cv_.notify_all();
    }

    void push(Task&& task) {
        {
            lock_guard<mutex> g(mtx_);
            if(done_) throw runtime_error("push task to a stopped queue.");
            q_.emplace_back(move(task));
        }
        cv_.notify_one();
    }

    void pop(Task& task) {
        unique_lock<mutex> lock(mtx_);
        // while(q_.empty() && !done_) cv_.wait(lock);
        cv_.wait(lock, [this]{ return !q_.empty() || done_; });
        if(q_.empty() && done_) return;
        task = move(q_.front());
        q_.pop_front();
    }

    // stealing 
    bool try_push(Task&& task) {
        {
            unique_lock<mutex> lock(mtx_, try_to_lock);
            if(!lock) return false;

            if(done_) throw runtime_error("push task to a stopped queue.");
            q_.emplace_back(move(task));
        }
        cv_.notify_one();
        return true;
    }

    bool try_pop(Task& task) {
        unique_lock<mutex> lock(mtx_, try_to_lock);

        if(!lock) return false;

        if(q_.empty()) return false;
        task = move(q_.front());
        q_.pop_front();
        return true;
    }
};

class task_system_single_queue {
/*
                                      / -> thread -> core
    task -> queue [t1, t2, ... ti...] - -> thread -> core
                                      \ -> thread -> core
*/
    const static unsigned capacity_{4};
    notification_queue q_;
    vector<thread> workers_;

    void run() {
        while(true) {
            Task task; 
            q_.pop(task);
            if(!task) return;
            task();
        }
    }
public:
    task_system_single_queue() {
        workers_.reserve(capacity_);
        for(unsigned index = 0; index < capacity_; ++index) {
            workers_.emplace_back([this]{ run(); });
        }
    }

    ~task_system_single_queue() {
        q_.stop();
        for(auto& worker : workers_) if(worker.joinable()) worker.join();
    }

    task_system_single_queue(const task_system_single_queue&) = delete;
    task_system_single_queue& operator=(const task_system_single_queue&) = delete;

    void async(Task&& task) {
        q_.push(move(task));
    }
};

/*
    ^ single queue: high contention, other threads are blocking at the pop
    bad performance: 1
    improvement: have queue per thread, reduce the contention.
*/

class task_system_multi_queue {
/*
                        / -> queue [t1, t2, ... ti...] -> thread -> core
    task -> scheduler ->  -> queue [t1, t2, ... ti...] -> thread -> core
                        \ -> queue [t1, t2, ... ti...] -> thread -> core
*/
    const static unsigned capacity_{4};
    vector<notification_queue> qs_;
    vector<thread> workers_;
    atomic<unsigned> index_{0}; // scheduler -> which queue to go

    void run(unsigned index) {
        while(true) {
            Task task;
            qs_[index].pop(task);
            if(!task) return;
            task();
        }
    }
public:
    task_system_multi_queue() : qs_(capacity_) {
        workers_.reserve(capacity_);
        for(unsigned index = 0; index < capacity_; ++index) {
            workers_.emplace_back([this, index]{ run(index); });
        }
    }

     ~task_system_multi_queue() {
        for(auto& q : qs_) q.stop();
        for(auto& worker : workers_) if(worker.joinable()) worker.join();
    }

    task_system_multi_queue(const task_system_multi_queue&) = delete;
    task_system_multi_queue& operator=(const task_system_multi_queue&) = delete;

    void async(Task&& task) {
        // round robin: relax, oder dones't metter, increment is enough
        const auto cur = index_.fetch_add(1, memory_order_relaxed);
        qs_[cur % capacity_].push(move(task));
    }
};

/*
    ^ multi queue: lower contention,
    better performance: 10
    problem:
        1. all long running task get into one queue and other threads are idle
        2. even in a fully loaded system, we can end up with fair amount of contentions on each queue.

    improvement: 
        task stealing, if a thread is idle, it can steal a task from other threads queue.
*/

class task_system_multi_queue_stealing {
/*
in order to steal, we need the notification_queue to beable to try_push/try_pop 

                        / -> queue [t1, t2, ... ti...] \       /-> thread -> core
    task -> scheduler ->  -> queue [t1, t2, ... ti...] - steal --> thread -> core
                        \ -> queue [t1, t2, ... ti...] /       \-> thread -> core
*/
    const static unsigned capacity_{4};
    const static unsigned K = 2; // how many times we try to steal from all queues

    vector<notification_queue> qs_;
    vector<thread> workers_;

    atomic<unsigned> index_{0}; // scheduler -> which queue to go


    void run(unsigned index) {
        while(true) {
            Task task;
            for (unsigned i = 0; i < capacity_; ++i) {
                if(qs_[(index + i)%capacity_].try_pop(move(task))) break;
            }
            if(!task) qs_[index].pop(task); // fallback
            if(!task) return;
            task();
        }
    }
public:
    task_system_multi_queue_stealing() : qs_(capacity_) {
        workers_.reserve(capacity_);
        for(unsigned index = 0; index < capacity_; ++index) {
            workers_.emplace_back([this, index]{ run(index); });
        }
    }

     ~task_system_multi_queue_stealing() {
        for(auto& q : qs_) q.stop();
        for(auto& worker : workers_) if(worker.joinable()) worker.join();
    }

    task_system_multi_queue_stealing(const task_system_multi_queue_stealing&) = delete;
    task_system_multi_queue_stealing& operator=(const task_system_multi_queue_stealing&) = delete;

    void async(Task&& task) {
        const auto cur = index_.fetch_add(1, memory_order_relaxed);
        for(unsigned i = 0; i < capacity_ * K; ++i) {
            if(qs_[(cur + i) % capacity_].try_push(move(task))) return;
        }
        qs_[cur % capacity_].push(move(task));
    }
};

// usage: 
template<typename Function, typename... Args> 
auto async(task_system_multi_queue_stealing& task_system, Function&& f, Args&&... args)
-> future<invoke_result_t<Function, Args...>> {
    using return_type = invoke_result_t<Function, Args...>;

    auto task = make_shared<packaged_task<return_type()>>(
        [
            f_ = forward<Function>(f),
            args_ = make_tuple(forward<Args>(args)...)
        ] -> return_type {
            return apply(move(f_), move(args_));
        }
    );

    auto future = task.get_future();
    task_system.async([task]{ (*task)(); });
    return future;
}