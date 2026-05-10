#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>

#include <iostream>

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this, i] {
                std::cout << "Worker " << i << " started." << " Thread ID: " << std::this_thread::get_id() << std::endl;
                while(true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // 等待直到有任务或池子停止
                        this->cv.wait(lock, [this]{ 
                            return this->stop || !this->tasks.empty(); 
                        });
                        if(this->stop && this->tasks.empty()) return;
                        task = std::move(this->tasks.front());

                        std::cout << "Worker " << i << " woke up." << " got a task." << std::endl;
                        this->tasks.pop();
                    }
                    task(); // 执行任务
                }
            });
        }
    }

    // 提交任务到池中
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        // 使用 packaged_task 包装函数，以便获取返回值
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        cv.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        cv.notify_all();
        for(std::thread &worker: workers) worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop;
};


int main() {
    ThreadPool pool(4); // 创建一个拥有4个线程的池子

    
    // 提交一个简单的 lambda 任务
    auto result = pool.enqueue([](int answer) {
        std::cout << "Task is running in thread: " << std::this_thread::get_id() << std::endl;
        return answer;
    }, 42);

    // 获取结果
    std::cout << "Result: " << result.get() << std::endl;

    return 0;
}