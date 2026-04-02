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
