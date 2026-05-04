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

    void* allocate(std::size_t size,
                   std::size_t alignment = alignof(std::max_align_t)) {

        std::size_t current = reinterpret_cast<std::size_t>(buffer_) + offset_;
        std::size_t space = capacity_ - offset_;

        void* ptr = reinterpret_cast<void*>(current);

        if (std::align(alignment, size, ptr, space)) {
            std::size_t new_offset =
                reinterpret_cast<std::size_t>(ptr) -
                reinterpret_cast<std::size_t>(buffer_) + size;

            if (new_offset > capacity_) {
                throw std::bad_alloc();
            }

            offset_ = new_offset;
            return ptr;
        }

        throw std::bad_alloc();
    }

    void reset() { offset_ = 0; }

    std::size_t used() const { return offset_; }
    std::size_t capacity() const { return capacity_; }

private:
    std::byte* buffer_;
    std::size_t capacity_;
    std::size_t offset_;
};


/* adapter to make it compatible for std usage */
template <class T>
class ArenaAllocator {
public:
    using value_type = T;

    ArenaAllocator(BufferAllocator& arena) noexcept
        : arena_(&arena) {}

    template <class U>
    ArenaAllocator(const ArenaAllocator<U>& other) noexcept
        : arena_(other.arena_) {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(
            arena_->allocate(n * sizeof(T), alignof(T))
        );
    }

    void deallocate(T*, std::size_t) noexcept {
        // no-op (arena allocator)
    }

    template <class U>
    bool operator==(const ArenaAllocator<U>& other) const noexcept {
        return arena_ == other.arena_;
    }

    template <class U>
    bool operator!=(const ArenaAllocator<U>& other) const noexcept {
        return !(*this == other);
    }

private:
    template <class>
    friend class ArenaAllocator;

    BufferAllocator* arena_;
};


#include <iostream>
alignas(std::max_align_t)
std::byte static_buffer[4096]; // 全局/静态区


int main() {
    {
        BufferAllocator arena(static_buffer, sizeof(static_buffer));

        int* a = static_cast<int*>(arena.allocate(sizeof(int)));
        *a = 42;   

        ArenaAllocator<int> alloc(arena);
        std::vector<int, ArenaAllocator<int>> v(alloc);

        v.push_back(1);
    }


    {
        alignas(std::max_align_t) std::byte stack_buffer[1024];
        //std::byte stack_buffer[1024];

        BufferAllocator arena(stack_buffer, sizeof(stack_buffer));

        ArenaAllocator<int> alloc(arena);
        std::vector<int, ArenaAllocator<int>> v(alloc);

        v.push_back(1);
    }

    {
        std::size_t size = 4096;

        // heap buffer (RAII 管理)
        /*
        为什么 heap 默认是对齐的？ 不需要 alignas(std::max_align_t)

        因为 C++ 标准规定：

        ✔ 所有 new 分配的内存必须满足：

        “适合任何对象类型的对齐要求” */
        std::unique_ptr<std::byte[]> heap_buffer =
            std::make_unique<std::byte[]>(size);

        BufferAllocator arena(heap_buffer.get(), size);
        
        ArenaAllocator<int> alloc(arena);
        std::vector<int, ArenaAllocator<int>> v(alloc);
        
        v.push_back(1);
        // 不需要 delete[]，unique_ptr 自动释放
    }
}