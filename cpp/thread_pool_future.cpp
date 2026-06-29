#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <vector>
#include <iostream>
#include <thread>
#include <condition_variable>

class ThreadPool {
private:
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;
    bool stop_;
    std::mutex mtx_;
    std::condition_variable cv_;

public:
    ThreadPool(size_t capacity) : stop_(false) {
        for (size_t i = 0; i < capacity; ++i) {
            workers_.emplace_back([this]() {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx_);

                        cv_.wait(lock, [this]() { return !tasks_.empty() || stop_; });

                        if (stop_ && tasks_.empty()) {
                            return;
                        }
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task(); // Execute task outside the lock
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
        for (std::thread &worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // Prevent copying or moving of the ThreadPool itself
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template<typename F, typename... Args>
    auto push(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        // FIX: Added '...' to Args
        using return_type = std::invoke_result_t<F, Args...>; 
        // we need shared pointer because std::function is copiable, so the lambda should capture this by copy
        // but std::packaged_task itself is only movable
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mtx_);

            // Don't allow pushing tasks if the pool has stopped
            if (stop_) {
                throw std::runtime_error("Enqueue requested on stopped ThreadPool");
            }

            tasks_.push([task]() { 
                (*task)(); 
            });
            cv_.notify_one();
        }

        return res;
    }
};

int main() {
    // Wrapped in a block scope to demonstrate the destructor working safely
    {
        ThreadPool thread_pool(4);

        auto res_future = thread_pool.push([](int left, int right) { return left + right; }, 1, 2);
        std::cout << "Result: " << res_future.get() << std::endl;
    } 
    // ThreadPool safely destructs here

    return 0;
}