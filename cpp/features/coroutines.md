C++20 的协程（Coroutines）是近年来 C++ 最重大的特性之一。它不像 Python 或 Go 的协程那样“开箱即用”，而是一套**底层框架**。

简单来说，协程是**可以暂停执行并稍后恢复的函数**。

---

### 1. 核心概念：三个关键字

C++20 引入了三个新关键字，只要函数体中包含其中任何一个，该函数就变成了协程：

* **`co_await`**: 暂停协程的执行，直到某个异步任务完成。
* **`co_yield`**: 暂停执行并向调用者返回一个值（常用于生成器）。
* **`co_return`**: 结束协程并返回一个最终结果。

---

### 2. 协程的运行机制

不同于普通函数执行完就销毁栈帧，协程会将状态（局部变量、参数、暂停点等）存储在**堆（Heap）**上。



要实现一个协程，你必须定义一个**承诺对象（Promise Object）**，它是协程内部与外部通信的桥梁。编译器会根据你的 `promise_type` 生成复杂的模板代码。

---

### 3. 用途一：生成器（Generators）
这是最直观的用法。你可以像写循环一样生成一个无限序列，而不需要一次性分配所有内存。

#### 代码示例：
```cpp
#include <iostream>
#include <coroutine>

// 简化的 Generator 模板（实际使用建议用 std::generator，C++23 引入）
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        auto get_return_object() { return Generator{handle_type::from_promise(*this)}; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::terminate(); }
        auto yield_value(T value) {
            current_value = value;
            return std::suspend_always{};
        }
        void return_void() {}
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type h;

    bool next() { return h ? (h.resume(), !h.done()) : false; }
    T value() { return h.promise().current_value; }
};

// 协程函数
Generator<int> count_up(int start, int step) {
    while (true) {
        co_yield start; // 暂停并返回当前值
        start += step;
    }
}

int main() {
    auto gen = count_up(10, 5);
    for (int i = 0; i < 5; ++i) {
        gen.next();
        std::cout << gen.value() << " "; // 输出: 10 15 20 25 30
    }
}
```

---

### 4. 用途二：异步 I/O 与并发
这是协程最强大的地方。在编写网络服务或高并发应用时，你可以用**同步的写法编写异步的代码**，避免了传统回调（Callback）带来的“回调地狱”。
```
// 典型的回调地狱伪代码
connect(server, [](bool success) {
    if (success) {
        login(user, [](bool loggedIn) {
            if (loggedIn) {
                fetchUserInfo([](UserInfo info) {
                    updateUI(info, []() {
                        std::cout << "终于搞定了！" << std::endl;
                    });
                });
            } else {
                std::cout << "登录失败";
            }
        });
    } else {
        std::cout << "连接失败";
    }
});
```

#### 对比说明：
* **传统异步**：调用 `read()` -> 传入 Lambda 回调 -> 回调里再嵌套 `write()` 的回调。
* **C++20 协程**：
    ```cpp
    Task<void> handle_client(Socket socket) {
        auto data = co_await socket.async_read(); // 这里暂停，线程可以去干别的事
        // 当数据准备好时，协程自动在此恢复
        co_await socket.async_write(process(data)); 
    }
    ```

---

### 5. 为什么 C++20 协程这么难用？

你可能发现了，上面的 `Generator` 例子需要写大量的冗余代码（`promise_type` 等）。这是因为：
1.  **无状态/有状态权衡**：C++ 追求零开销（Zero-overhead），它不强制要求任何特定的运行时调度器。
2.  **高度可定制**：它允许开发者自己决定协程如何分配内存、如何调度、如何处理异常。

### 总结
* **优势**：极高性能（无栈协程，切换开销极小）、代码逻辑连贯、节省内存。
* **现状**：目前直接使用原生接口比较痛苦。在实际开发中，通常建议配合 **cppcoro** 库或者等待 **C++23/26** 标准库进一步完善（如 `std::generator` 和 `std::execution`）。

你目前是在尝试从零实现一个协程库，还是在寻找现成的库来解决具体的并发问题？