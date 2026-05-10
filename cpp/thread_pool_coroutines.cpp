#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <coroutine>
#include <functional>
#include <chrono>
#include <syncstream>

// 定义一个线程局部变量。每个线程都有自己独立的一份副本来保存逻辑 ID。
// 默认为 -1，代表主线程或其他非池内线程。
thread_local int current_worker_id = -1;

// 1. handler: 协程的核心，代表一个可挂起的执行点， 这个类的核心是持有一个 promise_type
// 这个类是给编译器用的，用户不需要直接操作它
struct AsyncTask {
    struct promise_type {
        // 当协程开始运行，先通过这个函数创建 AsyncTask 对象返回给调用者
        AsyncTask get_return_object() { return {}; }

        // 协程一启动是立即执行(never)还是先挂起(always)？通常选立刻执行
        std::suspend_never initial_suspend() { return {}; }

        // 协程执行完后，是否停留在终点？通常选不停留(never)以自动销毁
        std::suspend_never final_suspend() noexcept { return {}; }

        // 对应 co_return; 如果不写 return，默认调这个
        void return_void() {}

        // 如果协程里抛了异常没 catch，会进这里
        void unhandled_exception() { std::terminate(); }
    };
};

class CoroThreadPool {
public:
    CoroThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {

            workers.emplace_back([this, i] {
                current_worker_id = i;
                std::osyncstream(std::cout) 
                    << "[Worker " << current_worker_id << "] (" << std::this_thread::get_id() << "): "
                    << "started" << std::endl;

                while (true) {
                    std::coroutine_handle<> handle;
                    {
                        std::unique_lock<std::mutex> lock(this->mtx);
                        this->cv.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        handle = tasks.front();
                        std::osyncstream(std::cout) 
                            << "[Worker " << current_worker_id << "] (" << std::this_thread::get_id() << "): "
                            << "woke up and took a task.\n";
                        tasks.pop();
                    }
                    // 核心：在工作线程中恢复协程
                    handle.resume(); 
                }
            });
        }
    }

    void enqueue(std::coroutine_handle<> handle) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.push(handle);
        }
        cv.notify_one();
    }

    // 2. Awaiter: 桥接协程挂起与线程池调度， 主要用来改变代码的执行位置（从主线程传送到线程池）
    struct PoolAwaiter {
        CoroThreadPool& pool;
        
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
            std::osyncstream(std::cout) 
                << "[Worker " << current_worker_id << "] (" << std::this_thread::get_id() << "): "
                << "handle resumed.\n";
        }
    };

    // 提交入口：返回一个 Awaiter: 连接了业务代码和 Awaiter
    PoolAwaiter schedule() { return {*this}; }

    ~CoroThreadPool() {
        { std::unique_lock<std::mutex> lock(mtx); stop = true; }
        cv.notify_all();
        for (auto& t : workers) t.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::coroutine_handle<>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
};

// 3. 使用协程
AsyncTask run_task(CoroThreadPool& pool, int task_id) {
    // 1. 还在主线程中
    {
        // 构造一个临时的 osyncstream，它会在离开大括号 } 时一次性、原子地把内容刷入 cout
        std::osyncstream(std::cout) 
            << "[Main    ] (" << std::this_thread::get_id() << "): "
            << "Scheduling task " << task_id << " to thread pool...\n";
    }

    // --- 魔法发生，挂起协程并入队 ---
    co_await pool.schedule(); 
    // --------------------------------

    // 2. 以下代码已经在 Worker 线程里了
    {//task body    
        std::osyncstream(std::cout) 
            << "[Task   " << task_id << "] (" << std::this_thread::get_id() << "): "
            << " executed by Worker " << current_worker_id << "...\n";
             // 模拟工作负载
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

        // 3. 任务结束
        std::osyncstream(std::cout) 
            << "[Task   " << task_id << "] (" << std::this_thread::get_id() << "): "
            << " executed!\n";
    }
}

AsyncTask linear_dependency(CoroThreadPool& pool) {
    // 1. 执行任务 A
    co_await pool.schedule();
    std::osyncstream(std::cout) << "[Step A] Done\n";

    // 2. 执行任务 B (依赖 A)
    // 注意：这里不需要手动 enqueue，协程会自动在 A 结束后恢复并继续
    co_await pool.schedule(); 
    std::osyncstream(std::cout) << "[Step B] Done (A is finished)\n";

    // 3. 执行任务 C (依赖 B)
    co_await pool.schedule();
    std::osyncstream(std::cout) << "[Step C] Done\n";
}



// task with return value，can be waited by other waiter
template<typename T>
struct Task {
    struct promise_type {
        T result;
        std::coroutine_handle<> waiter; // 谁在等我

        Task get_return_object() { return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() { return {}; } // 设为 always 方便受控启动
        std::suspend_always final_suspend() noexcept {
            if (waiter) waiter.resume(); // 任务结束，唤醒等待我的父协程
            return {};
        }
        void return_value(T val) { result = val; } // 处理 co_return val
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    // 为了让别人能 co_await task
    bool await_ready() { return handle.done(); }
    void await_suspend(std::coroutine_handle<> w) { handle.promise().waiter = w; handle.resume(); }
    T await_resume() { return handle.promise().result; }

    ~Task() { if (handle) handle.destroy(); }
};

// 任务 A：返回 10
Task<int> task_A(CoroThreadPool& pool) {
    co_await pool.schedule(); // 切换到线程池
    std::osyncstream(std::cout) << "[Worker] Task A calculating...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    co_return 10;
}

// 任务 B：返回 20
Task<int> task_B(CoroThreadPool& pool) {
    co_await pool.schedule(); // 切换到线程池
    std::osyncstream(std::cout) << "[Worker] Task B calculating...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    co_return 20;
}

// 任务 C：依赖 A 和 B，计算总和
AsyncTask task_C(CoroThreadPool& pool) {
    // 启动 A 和 B
    auto tA = task_A(pool);
    auto tB = task_B(pool);

    // 挂起并等待结果
    // 这里会发生两次跳转：等 A 完了恢复，再等 B 完了恢复
    int valA = co_await tA;
    int valB = co_await tB;

    std::osyncstream(std::cout) << "[Worker] Task C summing: " << valA << " + " << valB 
                                << " = " << (valA + valB) << "\n";
}

int main() {
    CoroThreadPool pool(4);

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    run_task(pool, 1);
    run_task(pool, 2);
    run_task(pool, 3);
    linear_dependency(pool);
    task_C(pool); // 这个任务会启动 A 和 B 两个子任务，并等待它们完成

    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

/*
co_await 版本的线程池调度器相较于传统的 std::future 版本，具有以下几个显著优势：
1. 真正的“零拷贝”调度

在你的旧代码中，std::packaged_task 和 std::future 内部有复杂的共享状态和堆内存分配。
在协程版本中，我们直接传递 std::coroutine_handle<>。这个句柄本质上只是一个指针，非常轻量。
2. 线程切换的透明性

在旧代码中，你需要在主线程调用 result.get()，这会阻塞主线程。
而在协程版中，co_await 挂起时，主线程可以去做别的事情（比如继续处理 UI 事件或接收网络包），当线程池算好了，它会自动回到 co_await 之后的那一行继续走。
3. 性能优势

    没有 std::future 的锁开销：future.get() 内部涉及原子变量和等待队列，协程恢复直接通过函数指针跳转。

    内存友好：协程的帧（Frame）由编译器优化，通常比手动创建一堆 shared_ptr<packaged_task> 更省内存。

避坑指南

    生命周期：协程挂起后，局部变量依然存在于协程帧中，但要注意传入的 pool 引用不能在协程结束前析构。

    调度语义：这个简单的 Demo 没处理返回值。如果需要返回值，需要改造 PoolAwaiter 的 await_resume 让它返回数据。
*/