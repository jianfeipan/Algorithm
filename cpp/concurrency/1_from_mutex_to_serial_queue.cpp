#include <optional>
#include <unordered_map>
#include <deque>
#include <functional>

#include <mutex>
#include <future>
#include <thread>
#include <condition_variable>

#include <tuple>
#include <memory>
#include <utility>
using namespace std;
/*
NDC 2017 "Concurrency" Sean Parent
No raw synchronization primitives
*/

/*
Lock based model: 
    most engineers has a horrible understanding of mutex: other threads are waiting for the mutex whil one thread is using it.
 */

class registry {
    mutex mtx_;
    unordered_map<string, string> data_;
public:
    optional<string> get(const string& key) {
        lock_guard<mutex> g(mtx_);

        auto it = data_.find(key);
        if (it != data_.end()) return it->second;

        return nullopt;
    }

    void set(const string& key, const string& val) {
        lock_guard<mutex> g(mtx_);
        data_[key] = val;
    }
};

/* 
A mutex serializes access to a resource:
    the resource can be accessed only one at a time
    mutexes don't scale, don't compose, can deadlock
    Replace them with an explicit serial_queue gives you
        - fire-and-forget writes
        - future for read: can compose: continuation, join, split,...
*/

// serial queue: a single consumer wrapper of a notification queue
class serial_queue {
    deque<function<void()>> q_;
    mutex                   mtx_;
    condition_variable      cv_;
    bool                    done_ {false};
    thread                  worker_;

    void run() {
        deque<function<void()>> cache; 
        while (true) {
            {
                unique_lock<mutex> lock(mtx_);
                cv_.wait(lock, [&]{return done_ || !q_.empty(); });
                if (q_.empty() && done_) return;
                cache.swap(q_);
            }
            
            while (!cache.empty()) { // drai the queue
                cache.front()();
                cache.pop_front();
            }
        }
    }

public:
    serial_queue() : worker_([this]{ run(); }) { }
    ~serial_queue() {
        {
            lock_guard<mutex> g(mtx_);
            done_ = true;
        }
        cv_.notify_all();
        worker_.join();
    }

    serial_queue(const serial_queue&) = delete;
    serial_queue& operator=(const serial_queue&) = delete;

    template<typename F, typename ...Args>
    auto async(F&& f, Args&& ...args) -> future<invoke_result_t<F, Args...>>{
        using return_type = invoke_result_t<F, Args...>;

        auto p_task = make_shared<packaged_task<return_type()>>(
            [
                fn = forward<F>(f), 
                tup = make_tuple(forward<Args>(args)...)
            ]() mutable -> return_type {
                return apply(move(fn), move(tup));
            }
        );
        // apply+tup > invoke(f, args...) > bind : move only object, perfect forwarding

        auto future  = p_task->get_future();
        {
            lock_guard<mutex> lock(mtx_);
            q_.emplace_back([p_task] { (*p_task)(); });
        }
        cv_.notify_one();
        return future;
    }
};

// Any mutex based lock and be transform to a serial queue
class registry_serial {
    serial_queue sq_;
    unordered_map<string, string> data_;
public:
    future<optional<string>> get(const string& key) {
        return sq_.async([this, key]->optional<string> {
            auto it = data_.find(key);
            if(it!=data_.end()) return it->second;
            return nullopt;
        });
    }

    void set(const string& key, const string& val) {
        sq_.async([this, key, val]{data_[key] = val; });
    }

    // Bucket set: only possible we have the queue, but with mutex lock, it's not possible
    void set(const vector<pair<string, string>>& kvs) {
        sq_.async([this, kvs]{
            data_.insert(begin(kvs), end(kvs));
        });
    }
};

/*
cow: copy-on-write pattern: lock-free for Read-heavy / mostly immutable registry
    - read only can be done without locking
    - write access can be done by make a copy of the data modifying the copy, and then replace the ptr
*/

class registry_cow {
    using map = unordered_map<string, string>;
    atomic<shared_ptr<map>> data_{ make_shared<map>() }; // atomic<shared_ptr> C++20
    serial_queue sq_;

public:
    optional<string> get(const string& key) {
        auto snap = data_.load(memory_order_acquire);
        auto it = snap->find(key);
        if (it!=snap->end()) return it->second;
        return nullopt;
    }

     void set(const string& k, const string& v) {
        sq_.async([this, k, v]{
            auto new_snap = make_shared<map>(*data_.load(memory_order_acquire)); // we can only do copy, because read could happen any time.
            // this read here can be relaxed because our queue is serial which guarentees the read is after prev write
            (*new_snap)[k] = v;
            data_.store(new_snap, memory_order_release);
        });
     }
    
};