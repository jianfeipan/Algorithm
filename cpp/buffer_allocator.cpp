#include <cstddef>
#include <cassert>
#include <new>
#include <memory>
#include <vector>


/*

unique_ptr  → owns heap memory
      ↓
BufferAllocator → uses memory (non-owning)
      ↓
allocated objects


*/

class BufferAllocator {
public:
    BufferAllocator(std::byte* buffer, std::size_t size)
        : buffer_(buffer), capacity_(size), offset_(0) {}

    // no copy
    BufferAllocator(const BufferAllocator&) = delete;
    BufferAllocator& operator=(const BufferAllocator&) = delete;
    
    // move
    BufferAllocator(BufferAllocator&&) noexcept = default;
    BufferAllocator& operator=(BufferAllocator&&) noexcept = default;


    void* allocate(std::size_t size,
                   std::size_t alignment = alignof(std::max_align_t)) {

        void* ptr = buffer_ + offset_;
        std::size_t space = capacity_ - offset_;

        if (std::align(alignment, size, ptr, space)) {
            // ptr is now aligned, space has been decreased by the padding
            void* result = ptr;
            offset_ = (static_cast<std::byte*>(ptr) - buffer_) + size;
            return result;
        }

        throw std::bad_alloc();
    }

    void reset() { offset_ = 0; }

private:
    std::byte* buffer_;
    std::size_t capacity_;
    std::size_t offset_;
};


/* adapter to make it compatible for std usage */
template <class T>
class ArenaAllocator {
private:
    BufferAllocator* arena_;
public:
    //a standard boilerplate requirement for custom allocators that need to work with STL containers
    using value_type = T;

    ArenaAllocator(BufferAllocator& arena) noexcept
        : arena_(&arena) {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(
            arena_->allocate(n * sizeof(T), alignof(T))
        );
    }

    void deallocate(T*, std::size_t) noexcept {
        // no-op (arena allocator)
    }
};


#include <iostream>
#include <memory>
alignas(std::max_align_t)
std::byte static_buffer[4096]; // 全局/静态区


int main() {
    {
        BufferAllocator arena(static_buffer, sizeof(static_buffer));

        ArenaAllocator<int> alloc(arena);

        int* ptr = alloc.allocate(1);
        std::construct_at(ptr, 1);
        std::cout << *ptr<< std::endl;

        std::vector<int, ArenaAllocator<int>> v(alloc);
        v.push_back(1);
        std::cout << v[0]<< std::endl;

    }

    {
        // stack buffer
        alignas(std::max_align_t) std::byte stack_buffer[1024];
        //std::byte stack_buffer[1024];

        BufferAllocator arena(stack_buffer, sizeof(stack_buffer));

        ArenaAllocator<int> alloc(arena);

        int* ptr = alloc.allocate(1);
        std::construct_at(ptr, 1);
        std::cout << *ptr<< std::endl;

        std::vector<int, ArenaAllocator<int>> v(alloc);
        v.push_back(1);
        std::cout << v[0]<< std::endl;

    }

    {
        // heap buffer
        /*
        为什么 heap 默认是对齐的？ 不需要 alignas(std::max_align_t)

        因为 C++ 标准规定：

        ✔ 所有 new 分配的内存必须满足：

        “适合任何对象类型的对齐要求” */
        size_t size = 4096;
        std::unique_ptr<std::byte[]> heap_buffer = std::make_unique<std::byte[]>(size);
        BufferAllocator arena(heap_buffer.get(), size);
        
        ArenaAllocator<int> alloc(arena);

        int* ptr = alloc.allocate(1);
        std::construct_at(ptr, 1);
        std::cout << *ptr<< std::endl;


        std::vector<int, ArenaAllocator<int>> v(alloc);
        v.push_back(1);
        std::cout << v[0]<< std::endl;

        // 不需要 delete[]，unique_ptr 自动释放
    }
}