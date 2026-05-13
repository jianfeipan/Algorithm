#include <coroutine>
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <sstream>

inline std::mutex cout_mtx;
template<typename... Args>
void sync_print(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << std::forward<Args>(args));
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << oss.str();
}

inline thread_local int current_worker_id = -1;

template<typename T>
struct AsyncTask {
    struct promise_type {
        std::promise<T> result;

        AsyncTask get_return_object() {
            return { result.get_future() };
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void return_value(T value) { result.set_value(std::move(value)); }
        void unhandled_exception() { result.set_exception(std::current_exception()); }
    };

    std::shared_future<T> future;

    T get() { return future.get(); }
};

// Void specialization (keeps the old fire-and-forget behavior)
template<>
struct AsyncTask<void> {
    struct promise_type {
        AsyncTask get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

class ThreadPool {
private:
    std::vector<std::thread> workers_;
    std::queue<std::coroutine_handle<>> tasks_;
    bool stop_ = false;
    std::mutex mtx_;
    std::condition_variable cv_;

public:
    ThreadPool(size_t size) : stop_(false){
        for(int i=0; i<size; ++i) {
            workers_.emplace_back([this, i](){
                current_worker_id = i;
                while(true){
                    std::coroutine_handle<> handle;
                    {
                        std::unique_lock<std::mutex> lock(mtx_);
                        cv_.wait(lock, [this](){
                            return stop_ || !tasks_.empty();
                        });
                        if(stop_ && tasks_.empty()) return; // worker exit: stoped and no more job
                        handle = std::move(tasks_.front()); tasks_.pop();
                    }
                    handle.resume();
                }
            });
        }
    }

    ~ThreadPool(){
        stop();
        for(auto& worker : workers_) worker.join();
    }

    void stop(){
        {
            std::unique_lock<std::mutex> lock(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
    }

    void enqueue(std::coroutine_handle<> handle) {
        {
            std::unique_lock<std::mutex> lock(mtx_);
            tasks_.push(handle);
        }
        cv_.notify_one();
    }

    struct PoolAwaiter {
        ThreadPool& pool;

        // 1. 询问：已经到目的地了吗？
        // 返回 false 表示“还没到，请挂起函数”。
        bool await_ready() { return false; }

        // 挂起时执行：将当前协程句柄丢进任务队列
        // 2. 动作：既然要挂起，我们要把剩下的函数“句柄”存到哪？
        // 这个 handle 就代表 co_await 之后的全部逻辑。task body
        void await_suspend(std::coroutine_handle<> handle) {
            pool.enqueue(handle);
        }
        // 3. 结果：当 Worker 线程 resume 之后，co_await 表达式的返回值是什么？
        // 我们这里只负责切换线程，不返回数据，所以是 void。
        void await_resume() {
            sync_print("[Worker ", current_worker_id, "] (", std::this_thread::get_id(), "): handle resumed.\n");
        }
    };

    // 提交入口：返回一个 Awaiter: 连接了业务代码和 Awaiter
    PoolAwaiter schedule() { return {*this}; }

};

AsyncTask<int> run_task(ThreadPool& pool, int input) {
    // 1. 主线程
    sync_print("[Main    ] (", std::this_thread::get_id(), "): Scheduling task ", input, " to thread pool...\n");

    // --- 魔法发生，挂起协程并入队 ---
    co_await pool.schedule();


    // 2. Worker 线程
    sync_print("[Task   ", input, "] (", std::this_thread::get_id(), "): executed by Worker ", current_worker_id, "...\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    int result = input + 1;
    sync_print("[Task   ", input, "] (", std::this_thread::get_id(), "): done, returning ", result, "\n");

    co_return result;
}

AsyncTask<int> run_dependent_task(ThreadPool& pool, AsyncTask<int>& dep1, AsyncTask<int>& dep2) {
    // Wait for dependencies (blocks on main thread before co_await)
    int a = dep1.get();
    int b = dep2.get();
    sync_print("[Main    ] (", std::this_thread::get_id(), "): Scheduling task 3 (", a, " + ", b, ") to thread pool...\n");

    // Worker 线程
    co_await pool.schedule();

    sync_print("[Task   3] (", std::this_thread::get_id(), "): executed by Worker ", current_worker_id, ", computing ", a, " + ", b, "...\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    int result = a + b;
    sync_print("[Task   3] (", std::this_thread::get_id(), "): done, returning ", result, "\n");

    co_return result;
}

int main() {
    ThreadPool pool(4);

    auto t1 = run_task(pool, 1);
    auto t2 = run_task(pool, 2);
    auto t3 = run_dependent_task(pool, t1, t2);  // depends on t1 and t2

    sync_print("Result 1: ", t1.get(), "\n");
    sync_print("Result 2: ", t2.get(), "\n");
    sync_print("Result 3 (sum): ", t3.get(), "\n");

    return 0;
}
