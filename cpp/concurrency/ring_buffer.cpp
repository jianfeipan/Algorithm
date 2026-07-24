/*Implement a fixed-capacity ring buffer in C++ for a setting with one producer and multiple consumers.

Design a class that stores integers in a preallocated circular array and supports the following operations:

RingBuffer(int capacity) : initialize the buffer with a fixed capacity.
bool push(int value) : insert a value at the tail. Return false if the buffer is full.
bool pop(int& value) : remove the oldest value from the head and write it into value . Return false if the buffer is empty.
bool empty() const
bool full() const
Requirements:

All operations should run in O(1) time.
Use circular indexing to reuse freed space.
Do not resize the underlying storage.
Focus on the object-oriented design and correct ring-buffer behavior.
You may assume synchronization is handled externally; the main goal is to implement the ring-buffer logic correctly for a single-producer, multi-consumer use case.
After coding, briefly explain how you would adapt the design if true thread safety were required.
*/

#include <vector>
#include <iostream>
#include <cassert>

class SimpleRingBuffer {
public:
    explicit SimpleRingBuffer(size_t capacity)
        : buf_(capacity), capacity_(capacity), head_(0), tail_(0) {}

    bool push(int value) {
        if (full()) return false;
        buf_[tail_%capacity_] = value;
        ++tail_;
        return true;
    }

    bool pop(int& value) {
        if (empty()) return false;
        value = buf_[head_%capacity_];
        ++head_;

        return true;
    }

    bool empty() const { return head_ == tail_; }
    bool full()  const { return tail_ - head_ >= capacity_; }

private:
    std::vector<int> buf_;
    size_t capacity_;
    size_t head_;  // index of the oldest element
    size_t tail_;  // index of the next write position
};  

/*
    - make it generic with template and capacity as template parameter
    - capcity to be power of 2 will make the mask efficient to replace module
 */
template<typename T, size_t Capacity = 1024>
class RingBuffer {
   static_assert((Capacity > 2) && ((Capacity & (Capacity - 1)) == 0), "Capacity must be a power of 2");
public:
    RingBuffer()
        : head_(0), tail_(0) {}

    bool push(T value) {
        if (full()) return false;
        buf_[tail_&mask_] = value;
        ++tail_;
        return true;
    }

    bool pop(T& value) {
        if (empty()) return false;
        value = buf_[head_&mask_];
        ++head_;
        return true;
    }

    bool empty() const { return head_ == tail_; }
    bool full()  const { return tail_ - head_ >= capacity_; }

private:
    std::array<T, Capacity> buf_;
    constexpr size_t mask_ = Capacity - 1;

    size_t head_; 
    size_t tail_;
};
/*
 * Thread-safety adaptation for SPSC:
 */

#include <atomic>
#include <new>
#include <optional>
#include <memory>

template <typename T, size_t Capacity = 1024>
class SPSCQueue {
    static_assert((Capacity > 2) && ((Capacity & (Capacity - 1)) == 0), "Capacity must be a power of 2");

private:
    // inplace data container
    struct Slot {
        alignas(T) std::byte data[sizeof(T)];
    };

    Slot buffer_[Capacity];
    static constexpr size_t mask_ = Capacity - 1;

    // Align to 64 bytes to prevent false sharing between producer and consumer
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};

    // Cache the observer's position to reduce atomic contention
    alignas(64) size_t head_cache_{0}; 
    alignas(64) size_t tail_cache_{0};

    T* ptr_at(size_t index) {
        return reinterpret_cast<T*>(&buffer_[index & mask_].data);
    }

public:
    SPSCQueue() = default;

    ~SPSCQueue() {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_relaxed);
        while (h < t) {
            std::destroy_at(ptr_at(h));
            h++;
        }
    }

    // Standard SPSC: Delete copy/move
    SPSCQueue(const SPSCQueue&) = delete;
    SPSCQueue& operator=(const SPSCQueue&) = delete;
    PSCQueue(SPSCQueue&&) = delete;
    SPSCQueue& operator=(SPSCQueue&&) = delete;

    template <typename... Args>
    bool enqueue(Args&&... args) {
        size_t t = tail_.load(std::memory_order_relaxed);
        
        // Check cached head first to avoid expensive atomic load
        if (t - head_cache_ >= Capacity) {
            head_cache_ = head_.load(std::memory_order_acquire);
            if (t - head_cache_ >= Capacity) return false; // Truly full
        }

        std::construct_at(ptr_at(t), std::forward<Args>(args)...);
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }

    std::optional<T> dequeue() {
        size_t h = head_.load(std::memory_order_relaxed);

        // Check cached tail first
        if (h >= tail_cache_) {
            tail_cache_ = tail_.load(std::memory_order_acquire);
            if (h >= tail_cache_) return std::nullopt; // Truly empty
        }

        T* ptr = ptr_at(h);
        std::optional<T> res(std::move(*ptr));
        std::destroy_at(ptr);
        
        head_.store(h + 1, std::memory_order_release);
        return res;
    }
};


/*
 * Thread-safety adaptation for SPMC: multi consumers
 * */


template <typename T, size_t Capacity = 1024>
class SPMCQueue {

    static_assert((Capacity > 2) && ((Capacity & (Capacity - 1)) == 0), "Capacity must be a power of 2");

private:
    // inplace data container
    struct Slot {
        alignas(T) std::byte data[sizeof(T)];
    };

    Slot buffer_[Capacity];
    static constexpr size_t mask_ = Capacity - 1;

    // Align to 64 bytes to prevent false sharing between producer and consumer
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};

    // Cache the observer's position to reduce atomic contention
    alignas(64) size_t head_cache_{0}; 
    alignas(64) size_t tail_cache_{0};

    T* ptr_at(size_t index) {
        return reinterpret_cast<T*>(&buffer_[index & mask_].data);
    }

public:
    SPMCQueue() = default;

    ~SPMCQueue() {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_relaxed);
        while (h < t) {
            std::destroy_at(ptr_at(h));
            h++;
        }
    }

    // Standard SPSC: Delete copy/move
    SPMCQueue(const SPMCQueue&) = delete;
    SPMCQueue& operator=(const SPMCQueue&) = delete;
    PSCQueue(SPMCQueue&&) = delete;
    SPMCQueue& operator=(SPMCQueue&&) = delete;

    template <typename... Args>
    bool enqueue(Args&&... args) {
        size_t t = tail_.load(std::memory_order_relaxed);
        
        // Check cached head first to avoid expensive atomic load
        if (t - head_cache_ >= Capacity) {
            head_cache_ = head_.load(std::memory_order_acquire);
            if (t - head_cache_ >= Capacity) return false; // Truly full
        }

        std::construct_at(ptr_at(t), std::forward<Args>(args)...);
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }

    // multi consumer 
    std::optional<T> dequeue() {
        size_t h = head_.load(std::memory_order_relaxed); 
        // even multi consumer at head, we still do relax load, we rely on the CAS

        while (true) {
            size_t t = tail_.load(std::memory_order_acquire);
            if (h >= t) return std::nullopt; // Queue empty

            // Try to "claim" this head index before other consumers
            if (head_.compare_exchange_weak(h, h + 1, 
                                            std::memory_order_relaxed, 
                                            std::memory_order_relaxed)) {
                // Successfully claimed index 'h'
                auto& slot = buffer_[h & mask_];
                
                // Spin until producer finishes writing to this specific slot
                while (!slot.is_ready.load(std::memory_order_acquire)) {
                    slot.is_ready.wait(false, std::memory_order_relaxed);
                }

                T* ptr = ptr_at(h);
                std::optional<T> res(std::move(*ptr));
                std::destroy_at(ptr);

                // Reset flag for the next time this slot is used
                slot.is_ready.store(false, std::memory_order_release);
                return res;
            }
            // If CAS failed, 'h' is updated to the new head_ value automatically
            // and the loop continues to try the next slot.
        }
    }
};
