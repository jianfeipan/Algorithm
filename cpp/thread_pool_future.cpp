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
                        std::unique_lock<std::mutex> lock(this->mtx_);
                        
                        this->cv.wait(lock, [this]{ 
                            return this->stop || !this->tasks.empty(); 
                        });

                        if(this->stop && this->tasks.empty()) return;

                        task = std::move(this->tasks.front());
                        this->tasks.pop();

                        std::cout << "Worker " << i << " woke up and took a task." << std::endl;
                    }
                    task();
                }
            });
        }
    }

    template<class F, class... Args>
    std::future<std::invoke_result_t<F, Args...>> 
    enqueue(F&& f, Args&&... args) {
        using return_type = std::invoke_result_t<F, Args...>;

        // 使用 packaged_task 包装函数，以便获取返回值
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mtx_);
            if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        cv.notify_one();

        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx_);
            stop = true;
        }
        cv.notify_all();

        for(std::thread &worker: workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx_;
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