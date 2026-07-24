#include <cstddef>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class object_pool {
    union Node {
        alignas(T) std::byte storage[sizeof(T)];
        size_t next_free;
    };

    std::vector<Node> buffer_;
    size_t next_free_slot_ { 0 };
    size_t capacity_ { 0 };

    T* get_ptr_at(size_t index) noexcept {
        return reinterpret_cast<T*>(buffer_[index].storage);
    }

public:
    explicit object_pool(size_t capacity) 
        : buffer_(capacity), capacity_(capacity) {
        
        for (size_t i = 0; i < capacity; ++i) {
            buffer_[i].next_free = i + 1;
        }
    }

    ~object_pool() {
        std::vector<bool> is_free(capacity_, false);
        size_t current = next_free_slot_;
        while (current < capacity_) {
            is_free[current] = true;
            current = buffer_[current].next_free;
        }

        // Destroy only the active objects
        for (size_t i = 0; i < capacity_; ++i) {
            if (!is_free[i]) {
                get_ptr_at(i)->~T();
            }
        }
    }

    // Disable copying and moving explicitly
    object_pool(const object_pool&) = delete;
    object_pool& operator=(const object_pool&) = delete;
    object_pool(object_pool&&) = delete;
    object_pool& operator=(object_pool&&) = delete;

    template<typename... Args>
    T* create(Args&&... args) {
        if (next_free_slot_ >= capacity_) {
            throw std::bad_alloc();
        }

        const size_t allocated_index = next_free_slot_;
        
        next_free_slot_ = buffer_[allocated_index].next_free;

        T* addr = get_ptr_at(allocated_index);
        std::construct_at(addr, std::forward<Args>(args)...);
        return addr;
    }

    void destroy(T* obj) noexcept {
        if (!obj) return;

        auto* raw_buffer_start = reinterpret_cast<std::byte*>(buffer_.data());
        auto* raw_obj_ptr = reinterpret_cast<std::byte*>(obj);
        
        ptrdiff_t byte_offset = raw_obj_ptr - raw_buffer_start;
        const size_t index = byte_offset / sizeof(Node);

        obj->~T();

        buffer_[index].next_free = next_free_slot_;
        next_free_slot_ = index;
    }
};  

// ^ the destory is tricky: you need to know which index was that object
// a better solution is to use a Deleter to hold the index and return a unique_ptr who binds the ptr and the Deleter.


#include <cstddef>
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T>
class stable_object_pool {
    struct Node {
        alignas(T) std::byte storage[sizeof(T)];
        size_t next_free;
        bool is_active = false; // Makes safety tracking incredibly simple
    };

    std::vector<Node> buffer_;
    size_t next_free_slot_ = 0;
    size_t capacity_ = 0;

    void release_slot(size_t index) noexcept {
        buffer_[index].is_active = false;
        buffer_[index].next_free = next_free_slot_;
        next_free_slot_ = index;
    }

public:
    // Custom deleter that our unique_ptr will use-> helps to find which index to be release
    class Deleter {
        stable_object_pool* pool_;
        size_t index_;
    public:
        Deleter(stable_object_pool* pool, size_t index) : pool_(pool), index_(index) {}
        
        void operator()(T* ptr) const noexcept {
            ptr->~T();
            pool_->release_slot(index_);
        }
    };

    using pointer = std::unique_ptr<T, Deleter>;

    explicit stable_object_pool(size_t capacity) 
        : buffer_(capacity), capacity_(capacity) {
        for (size_t i = 0; i < capacity; ++i) {
            buffer_[i].next_free = i + 1;
        }
    }

    ~stable_object_pool() {
        for (auto& node : buffer_) {
            if (node.is_active) {
                reinterpret_cast<T*>(node.storage)->~T();
            }
        }
    }

    template <typename... Args>
    [[nodiscard]] pointer create(Args&&... args) {
        if (next_free_slot_ >= capacity_) {
            throw std::bad_alloc();
        }

        const size_t idx = next_free_slot_;
        Node& node = buffer_[idx];
        
        next_free_slot_ = node.next_free;
        node.is_active = true;

        T* obj_ptr = reinterpret_cast<T*>(node.storage);
        std::construct_at(obj_ptr, std::forward<Args>(args)...);

        // Hand ownership to unique_ptr, embedded with the exact index!
        return pointer(obj_ptr, Deleter(this, idx));
    }
};