#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstddef>
#include <new>
#include <vector>

// 智能选择跨平台的底层对齐分配函数
inline void* cross_platform_aligned_alloc(std::size_t alignment, std::size_t size) {
#if defined(_MSC_VER) // Windows
    return _aligned_malloc(size, alignment);
#else // Linux / macOS 及其他 POSIX 系统
    // 确保 size 是 alignment 的整数倍
    std::size_t remainder = size % alignment;
    if (remainder != 0) {
        size += (alignment - remainder);
    }
    return std::aligned_alloc(alignment, size); 
    // alignment：对齐字节数（必须是 2 的幂，且必须是目标平台支持的有效对齐值）。
    // size：要分配的内存大小（字节数）。【核心陷阱】它必须是 alignment 的整数倍！
    // 返回值：成功时返回指向分配内存的指针；失败时返回 nullptr。
#endif
}

inline void cross_platform_aligned_free(void* ptr) {
#if defined(_MSC_VER)
    _aligned_free(ptr);
#else
    std::free(ptr);
#endif
}

// 泛型对齐分配器
template <typename T, std::size_t Alignment>
struct aligned_allocator {
    //STL 容器会尝试从分配器中读取预定义的类内别名（Type Traits）
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;//用来表示两个迭代器（指针）之间距离的带符号整数类型（Signed Integer）： 距离类型 而不是 T*： 即便是两个T*， 他们计算结果之后是longlong 64

    aligned_allocator() noexcept = default;

    template <typename U> 
    aligned_allocator(const aligned_allocator<U, Alignment>&) noexcept {}
    /*
        这个构造函数被称为泛化拷贝构造函数（Generalized Copy Constructor），它是 C++ 分配器（Allocator）中最反直觉、但也最核心的设计之一。

        简单一句话解释：它是为了让 std::vector 在内部能够把为 T 准备的分配器，偷偷转换成能够分配其他隐藏节点类型（如 U）的分配器。

        如果不写这个构造函数，你的 aligned_allocator 在配合很多标准库容器（特别是红黑树结构的 std::map 或链表结构的 std::list）时，会直接编译报错。
        1. 为什么会有 aligned_allocator<T> 转成 aligned_allocator<U> 的需求？

        我们以 std::vector<T> 为例。虽然 vector 表面上只分配 T 类型的连续数组，但在其内部实现中，或者在其他更复杂的容器中，事情并没那么简单。

        假设你写了这样一行代码：
        C++

        std::vector<int, aligned_allocator<int, 64>> vec;

        你明确指定了分配器是 aligned_allocator<int, 64>。

        但如果你换成 std::list（双向链表）：
        C++

        std::list<int, aligned_allocator<int, 64>> my_list;

        这时候冲突就来了：

            你给的分配器是管理 int 的：aligned_allocator<int, 64>。

            但是 std::list 内部根本不分配 int！它分配的是链表节点（Node），这个节点不仅包含 int，还包含了前驱和后继指针 next 和 prev。

        为了分配这个链表节点，std::list 必须在内部把你的 aligned_allocator<int, 64> 偷偷“重绑（Rebind）”变成 aligned_allocator<Node, 64>。
        2. 这个构造函数在其中扮演什么角色？

        当容器内部成功把分配器重绑为 Node 类型后，它需要创建这个新分配器的实例。标准库容器会尝试用你传进去的 int 分配器，去初始化这个新的 Node 分配器：
        C++

        // std::list 内部伪代码
        aligned_allocator<int, 64> old_alloc; // 用户传进来的

        // 容器内部创建真正需要的 Node 分配器
        aligned_allocator<Node, 64> new_alloc(old_alloc); // 👈 这里触发了跨类型的拷贝构造！

        如果没有我们定义的那个 template <typename U> aligned_allocator(...) 构造函数，编译器会尝试寻找一个能够接受 aligned_allocator<int> 的 aligned_allocator<Node> 构造函数。因为它们是完全不同的两个类，编译器找不到对应的构造函数，就会直接抛出大面积的编译错误（通常会提示无法隐式转换）。
        3. 为什么这个构造函数的函数体是空的 {}？

        你可能注意到了，它的函数体里没有任何代码：
        C++

        template <typename U> 
        aligned_allocator(const aligned_allocator<U, Alignment>&) noexcept {}

        这是因为在我们的 aligned_allocator 中，它没有任何类成员变量（它是个无状态分配器，Stateless Allocator）。

        所有的 aligned_allocator（不论它服务于 int、float 还是任何 Node）唯一的共同行为就是调用底层的 std::aligned_alloc。由于没有状态需要拷贝，我们只需要允许这种跨类型的转换发生即可，函数体内部什么都不需要做。
    */

    T* allocate(std::size_t n) {
        if (n == 0) return nullptr;
        
        // 检查对齐量是否为 2 的幂且是 sizeof(void*) 的倍数
        static_assert((Alignment & (Alignment - 1)) == 0, "Alignment must be a power of 2");
        
        std::size_t total_size = n * sizeof(T);
        void* ptr = cross_platform_aligned_alloc(Alignment, total_size);
        /*
            std::size_t remainder = size % alignment;
            if (remainder != 0) {
                size += (alignment - remainder);
            }
            void* ptr = std::aligned_alloc(alignment, size); 
        */ 
        
        if (!ptr) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(ptr);
    }

    void deallocate(T* ptr, std::size_t) noexcept {
        cross_platform_aligned_free(ptr);
    }

    // 支撑非同类型间的拷贝构造（如 std::vector 内部节点）
    template <typename U>
    struct rebind {
        using other = aligned_allocator<U, Alignment>;
    };

    bool operator==(const aligned_allocator&) const noexcept { return true; }
    bool operator!=(const aligned_allocator&) const noexcept { return false; }
};