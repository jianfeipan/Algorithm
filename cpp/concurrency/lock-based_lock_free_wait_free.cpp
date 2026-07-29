#include <mutex>
#include <shared_mutex>

#include <atomic>

#include <memory>

// lock-based
/* 
use mutual extlusive primitives (mutex) to protect critical section, 
    only one thread execute the critical seconstion, others wait (block).
problems: 
    deadlock, priority, cpmtext-switching
pros: 
    simple
*/
class registy_mutex{
    std::mutex mtx_;
    size_t count_{0};
public:
    size_t read(){  std::unique_lock lock(mtx_); return count_; }
    void increment(size_t i){  std::lock_guard g(mtx_); count_ += i; }
};

class registy_shared_mutex{
    std::shared_mutex shared_mtx_;
    size_t count_{0};
public:
    size_t read(){ std::shared_lock lock(shared_mtx_); return count_; } 
    void increment(size_t i){ std::unique_lock ulock(shared_mtx_); count_ += i; }
};

class spin_lock {
    std::atomic_flag flag_{ATOMIC_FLAG_INIT};
public:
    void lock() {
        // while(flag_.test_and_set(std::memory_order_relaxed)){ _mm_pause(); }
        /*
        logically, this works, but test_and_set is a unconditional write symentic, will triger RFO = Read For Ownership
            1. broadcast invalidate to all cores who has this cache line
            2. wait for all ack from incalidation
            3. write data
        This is on symentic level not data level, so even it's same value, this always happens. 
        So frequent `test_and_set` will generate huge traffic of RFO, if it's NUMA, UPI/mesh bus iwll be occupied by meaningless cohrence message. 
        */ 
        
        /*better solution is two loops: TTAS: test test_and_set*/
        size_t back_off = 1;
        while(true) {
            while(flag_.test(std::memory_order_relaxed)) { // read only, no RFO 
                for (size_t i=0; i<back_off; ++i) __mm_pause(); //backoff
                back_off *= 2;
            }

            if(!flag_.test_and_set(std::memory_order_acquire)) return; // lock seeceeds
        }
    }

    void unlock() {
        // unconditional write: RFO-> hidden cost with spin lock, unlock is expensive!
        flag_.clear(std::memory_order_release);
    }

    bool try_lock() {
        if (flag_.test(std::memory_order_relaxed)) return false;
        
        return !flag_.test_and_set(std::memory_order_acquire);
        // if old value is true, return !true -> lock fails because it's locked by other thread
        // if old value is false, I set it to true, reutrn !false -> lock succeed, 
    }
};

/*
lock-free: 
    No blocks, use atomic CAS in a retry loop: at least one thread makes progress in a finite number of steps, 
    no thread depends on other threads.
problems:
    hard ot desihne, ABA problem, memory reclamation, memory order reasoning, starvation
pros:
    no dead lock, better latency, no contex switching and thread suspend.

*/
template<typename T>
class lock_free_stack {
    struct Node {
        T val;
        std::shared_ptr<Node> next;
    };

    // std::atomic<Node*> top_{nullptr}; // raw pointer has ABA problem
    std::atomic<std::shared_ptr<Node>> top_{nullptr};

public:
    bool top(T& val) {
        auto top = top_.load(std::memory_order_acquire);
        if (!top) return false;
        val = top->val;// top is shared_ptr, top->val won't be race condition use-after-delete
        return true;
    }

    bool pop() {
        auto top = top_.load(std::memory_order_relaxed); 
        // loop CAS will guarentee the atomicity, 
        // no need to do it here, anything can happen between this and CAS
        if(!top) return false;

        while(!top_.compare_exchange_weak(
            top,
            top->next,
            std::memory_order_release, //success: write top_
            std::memory_order_relaxed // failure: read new top
        )) {
            if(!top) return false; // nothing to pop
        }
        return true;
    }

    void push(T&& val) {
        auto new_node = std::make_shared<Node>{std::move(val), top_.load(std::memory_order_relaxed)};
        
        while(!top_.compare_exchange_weak(
            new_node->next, // expect top_ is new_node->next
            new_node, // write new_node to top_
            std::memory_order_release, //success: write top_
            std::memory_order_relaxed // failure: read new top
        )) {}
    }
};

/*
wait-free:
    every thread competes its operatin in a bounded number of steps. 
    no loops depend on other threads,
pros:
    no deadlock, no starvation,
*/ 
class registy_wait_free{
    std::atomic<size_t> count_{0};
public:
    size_t read(){  return count_.load(std::memory_order_acquire); }
    void increment(size_t i){  count_.fetch_add(i, std::memory_order_release); }
};

