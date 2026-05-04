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


template<typename T, size_t Capacity = 1024>
class LFQueue{
    // & (1 cycle) much faster than % (loop)
    // 100000 & 011111 -> Capacity - 1 will be the mask
    static assert(Capacity & (Capacity-1) == 0, "capacity must be a power of 2");

public:
    LFQueue()
    : m_buffer(new T[Capacity])
    , m_mask(Capacity-1)
    , m_head()
    , m_tial()
    {}

    ~LFQueue(){delete[] m_buffer;}

    // no copy
    LFQueue(const LFQueue&) = delete;
    LFQueue& operator=(const LFQueue&) = delete;

    optional<T>  pop(){
        // called only by consumer, only write/read head: concurrency to read tail
        auto current = m_head.load(memory_order_relaxed);

        auto tail = m_tail.load(memory_order_aquire);
        // when proucer is writing, i need my read (next lines) after this aquire instruction
        if(current == tail) return nullopt;

        T data = m_buffer[current];// copy here!

        auto nextHead = (current + 1) & m_mask;
        // make sure the release after the change instructions
        // publisher will have concurreny on it
        m_head.sore(nextHead, memory_order_release);
        return data;
    }

    bool push(T&& val){
        // producer is w/r the tail, no concurency
        auto current = m_tail.load(memory_order_relaxed);
        auto nextTail = (current + 1) & m_mask;
        // producer has concurrency with consumer on reading head,
        // we aquire here to make sure my read is after producer's modification & release
        auto head = m_head.load(memory_order_aquire);

        if(nextTail == head) return false; // queue full

        m_buffer[nextTail] = move(val);
        // make sure to writ data instruction then release
        // so producer can have the newest data
        m_tail.store(expected, memory_order_release);
        return true;
    }

private:
    T* m_buffer; // 8B
    const size_t m_mask; //8B
    alignas(64) atomic<size_t> m_head; // 8B false share
    alignas(64) atomic<size_t> m_tail; // 8B
}


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
