#include <atomic>
#include <optional>
#include <cstddef>
#include <memory>

template <typename T, size_t Capacity>
class SPSCQueue {
    static_assert(Capacity >= 2, "Capacity must be >= 2");
    static_assert((Capacity & (Capacity - 1)) == 0,
                  "Capacity must be power of 2");

public:
    SPSCQueue() = default;

    ~SPSCQueue() {
        // consumer owns destruction responsibility
        while (dequeue().has_value()) {}
    }

    SPSCQueue(const SPSCQueue&) = delete;
    SPSCQueue& operator=(const SPSCQueue&) = delete;

    // -----------------------
    // Producer (ONLY 1)
    // -----------------------
    template <typename... Args>
    bool enqueue(Args&&... args) {
        size_t head = head_.load(std::memory_order_relaxed);
        size_t next = head + 1;

        if (next - tail_.load(std::memory_order_acquire) > Capacity)
            return false; // full

        std::construct_at(ptr(head), std::forward<Args>(args)...);

        head_.store(next, std::memory_order_release);
        return true;
    }

    // -----------------------
    // Consumer (ONLY 1)
    // -----------------------
    std::optional<T> dequeue() {
        size_t tail = tail_.load(std::memory_order_relaxed);

        if (tail == head_.load(std::memory_order_acquire))
            return std::nullopt; // empty

        T* ptr = this->ptr(tail);
        T value = std::move(*ptr);

        std::destroy_at(ptr);

        tail_.store(tail + 1, std::memory_order_release);

        return value;
    }

private:
    using Storage = std::aligned_storage_t<sizeof(T), alignof(T)>;

    static constexpr size_t mask_ = Capacity - 1;

    alignas(64) std::atomic<size_t> head_{0}; // producer only writes
    alignas(64) std::atomic<size_t> tail_{0}; // consumer only writes

    Storage buffer_[Capacity];

    T* ptr(size_t i) {
        return std::launder(
            reinterpret_cast<T*>(&buffer_[i & mask_])
        );
    }
};