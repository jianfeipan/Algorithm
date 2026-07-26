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
    unordered_map<string, string> data_;
    mutex mtx_;
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
    using Task = function<void()>;
    deque<Task> q_;
    thread worker_;
    mutex mtx_;
    condition_variable cv_;
    bool stop_{false};

    void run() {
        deque<Task> local_cache;
        while(true) {
            {
                unique_lock<mutex> lock(mtx_);
                cv_.wait(lock, [this]{ return !q_.empty() || stop_; }); 
                if (q_.empty() && stop_) return;
                swap(q_, local_cache);
            }

            while(!local_cache.empty()) { // single thread: run all task
                move(local_cache.front())();
                local_cache.pop_front();
            }
        }
    }
public:
    serial_queue() : worker_([this]{ run(); }){}

    ~serial_queue() {
        {
            lock_guard<mutex> g(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
        if (worker_.joinable()) worker_.join();
    }

    serial_queue(const serial_queue&) = delete;
    serial_queue& operator=(const serial_queue&) = delete;

    void async(Task&& task) {
        lock_guard<mutex> g(mtx_);
        q_.emplace_back(move(task));
        cv_.notify_one();
    }

    // more powerful async allowing return and input
    template <typename F, typename... Args>
    auto async(F&& f, Args&&... args) {
        using return_type = std::invoke_result_t<F, Args...>;

        // Bind function and args directly inside a simple lambda capture
        // auto bound_fn = [fn = std::forward<F>(f), 
        //                 ...args = std::forward<Args>(args)]() mutable {
        //     return std::invoke(std::move(fn), std::move(args)...);
        // };

        // auto task = std::make_shared<std::packaged_task<return_type()>>(std::move(bound_fn));
        // std::bind_front automatically binds and stores the args cleanly
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind_front(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        auto future = task->get_future();

        {
            std::lock_guard<std::mutex> lock(mtx_);
            q_.emplace_back([task] { (*task)(); });
        }
        cv_.notify_one();
        return future;
    }
};

// Any mutex based lock and be transform to a serial queue
class registry_serial {
    using map_t = unordered_map<string, string>;
    shared_ptr<map_t> data_ = make_shared<map_t>();
    serial_queue q_;

public:
    future<optional<string>> get(const string& key) {
        using return_type = optional<string>;
        auto task = make_shared<packaged_task<return_type()>>(
            [data_ = data_, key] -> return_type {
                auto it = data_->find(key);
                if(it != data_->end()) return it->second;
                return nullopt;
            }
        );

        auto future = task->get_future();

        q_.async([task]{ (*task)(); });
        return future;
    }

    void set(const string& key, const string& val) {
        q_.async( [data_ = data_, key, val] { 
            (*data_)[key] = val; }
        );
    } 
    // Bucket set: only possible we have the queue, but with mutex lock, it's not possible
    void set(vector<pair<string, string>> kvs) {
        q_.async( [data_ = data_, kvs = move(kvs)] { 
            data_->insert(make_move_iterator(begin(kvs)), make_move_iterator(end(kvs))); }
        );
    }
};

/*
cow: copy-on-write pattern: lock-free for Read-heavy / mostly immutable registry
    - read only can be done without locking
    - write access can be done by make a copy of the data modifying the copy, and then replace the ptr
*/

class registry_cow {
    using map_t = unordered_map<string, string>;
    atomic<shared_ptr<map_t>> data_{make_shared<map_t>()};
    serial_queue q_;

public:
    optional<string> get(const string& key) {
        auto snapshot = data_.load(memory_order_acquire);
        auto it = snapshot->find(key);
        if(it != snapshot->end()) return it->second;
        return nullopt;
    }

    void set(const string& key, const string& val) {
        q_.async( [this, key, val] { 
            auto snapshot = data_.load(memory_order_acquire); //can be relaxed 
            // this read here can be relaxed because our queue is serial which guarentees the read is after prev write           
            auto copy = make_shared<map_t>(*snapshot);// we can only do copy, because read could happen any time.
            (*copy)[key] = val; 
            data_.store(copy, memory_order_release); // to pair the reader
        });
    } 
};