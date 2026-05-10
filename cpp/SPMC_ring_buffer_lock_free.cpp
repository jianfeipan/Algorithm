/*Implement a fixed-capacity ring buffer in C++ for a setting with one producer and multiple consumers.

Design a class that stores integers in a preallocated circular array and supports the following operations:

RingBuffer(int capacity) : initialize the buffer with a fixed capacity.
bool push(int value) : insert a value at the tail. Return false if the buffer is full.
bool pop(int& value) : remove the oldest value from the head and write it into value . Return false if the buffer is empty.
bool empty() const
bool full() const
int size() const
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

class RingBuffer {
public:
    RingBuffer(int capacity)
        : buf_(capacity), capacity_(capacity), head_(0), tail_(0), count_(0) {}

    bool push(int value) {
        if (full()) return false;
        buf_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
        return true;
    }

    bool pop(int& value) {
        if (empty()) return false;
        value = buf_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        return true;
    }

    bool empty() const { return count_ == 0; }
    bool full()  const { return count_ == capacity_; }
    int  size()  const { return count_; }

private:
    std::vector<int> buf_;
    int capacity_;
    int head_;  // index of the oldest element
    int tail_;  // index of the next write position
    int count_; // number of elements currently in the buffer
};

/*
 * Thread-safety adaptation for true SPMC:
 *
 * 1. Use std::atomic<int> for head_ and count_ (consumers contend on these).
 *    tail_ is only written by the single producer, but read by consumers
 *    (through size/full/empty), so make it atomic too.
 *
 * 2. pop() must atomically claim a slot. A lock-free approach:
 *      - Use a CAS loop on head_: each consumer tries
 *        compare_exchange_weak(old_head, (old_head+1) % cap).
 *        Only the winner reads buf_[old_head].
 *      - Decrement count_ atomically after a successful pop.
 *
 * 3. push() is simpler (single producer): just needs an atomic
 *    store-release on tail_ and count_ so consumers see the new element.
 *
 * 4. Memory ordering: use acquire/release semantics—
 *      - Producer: store-release on tail_/count_ after writing buf_.
 *      - Consumer: load-acquire on tail_/count_ before reading buf_.
 *
 * 5. Alternatively, protect the whole buffer with a std::mutex
 *    (simpler but slower under high contention).
 */


#include <atomic>
#include <optional>
#include <cstddef>
#include <memory>      // construct_at, destroy_at
#include <type_traits>

template <typename T, size_t Capacity>
class SPMCQueue {
    static_assert(Capacity >= 2, "Capacity must be >= 2");
    static_assert((Capacity & (Capacity - 1)) == 0,
                  "Capacity must be a power of 2");

public:
    SPMCQueue() = default;

    ~SPMCQueue() {
        // ⚠️ 假设此时没有并发访问
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_relaxed);

        for (size_t i = tail; i < head; ++i) {
            auto* ptr = ptr_at(i);
            std::destroy_at(ptr);
        }
    }

    // 禁止拷贝（典型 lock-free 结构）
    SPMCQueue(const SPMCQueue&) = delete;
    SPMCQueue& operator=(const SPMCQueue&) = delete;

    // 允许移动（可选）
    SPMCQueue(SPMCQueue&&) = delete;
    SPMCQueue& operator=(SPMCQueue&&) = delete;

    // ---------------------------
    // Single Producer
    // ---------------------------
    template <typename... Args>
    bool enqueue(Args&&... args) {
        size_t head = head_.load(std::memory_order_relaxed);
        size_t next = head + 1;

        if (next - tail_.load(std::memory_order_acquire) > Capacity) { 
            // tail_， head_只在读取元素的时候才&mask， 否则 next == tail 无法判定是空还是满
            // 他们都是size_t:  这使得即使溢出了也是回到0, 还是符合逻辑的。
            return false; // full
        }

        auto* ptr = ptr_at(head);
        std::construct_at(ptr, std::forward<Args>(args)...);

        head_.store(next, std::memory_order_release);
        return true;
    }

    // ---------------------------
    // Multiple Consumers
    // ---------------------------
    std::optional<T> dequeue() {
        size_t tail;

        while (true) {
            tail = tail_.load(std::memory_order_relaxed);
            size_t head = head_.load(std::memory_order_acquire);

            if (tail >= head) {
                return std::nullopt; // empty
            }

            if (tail_.compare_exchange_weak(
                    tail,
                    tail + 1,
                    std::memory_order_acq_rel,
                    std::memory_order_relaxed)) {
                break;
            }
        }

        auto* ptr = ptr_at(tail);

        T value = std::move(*ptr);
        std::destroy_at(ptr);

        return value;
    }

private:
    using Storage = std::aligned_storage_t<sizeof(T), alignof(T)>;

    static constexpr size_t mask_ = Capacity - 1;

    // 避免 false sharing
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};

    Storage buffer_[Capacity];

    // 统一取指针（带 launder 更严谨）
    T* ptr_at(size_t index) {
        void* slot = &buffer_[index & mask_];
        return std::launder(reinterpret_cast<T*>(slot));
    }
};


// ─── demo / basic tests ───
int main() {
    RingBuffer rb(3);

    assert(rb.empty());
    assert(!rb.full());
    assert(rb.size() == 0);

    // fill the buffer
    assert(rb.push(10));
    assert(rb.push(20));
    assert(rb.push(30));
    assert(rb.full());
    assert(!rb.push(40));  // buffer is full

    // pop all elements in FIFO order
    int v;
    assert(rb.pop(v) && v == 10);
    assert(rb.pop(v) && v == 20);
    assert(rb.pop(v) && v == 30);
    assert(rb.empty());
    assert(!rb.pop(v));    // buffer is empty

    // wrap-around: push after pop to exercise circular indexing
    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb.full());
    assert(rb.pop(v) && v == 1);
    rb.push(4);            // wraps around
    assert(rb.pop(v) && v == 2);
    assert(rb.pop(v) && v == 3);
    assert(rb.pop(v) && v == 4);
    assert(rb.empty());

    std::cout << "All tests passed!\n";
    return 0;
}
