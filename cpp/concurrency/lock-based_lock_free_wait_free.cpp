#include <mutex>
#include <shared_mutex>

#include <atomic>


// lock-based
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

/*
lock-free
*/
template<typename T>
class lock_free_stack {
    struct Node {
        T val;
        Node* next{nullptr};
    };

    std::atomic<Node*> top_{nullptr};
public:
    bool top(T& val) {
        auto top = top_.load(std::memory_order_acquire);
        if (!top) return false;
        val = top->val;
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
        delete top;
        return true;
    }

    void push(T val) {
        auto* new_node = new Node{val, top_.load(std::memory_order_relaxed)};
        while(!top_.compare_exchange_weak(
            new_node->next, // expect top_ is new_node->next
            new_node, // write new_node to top_
            std::memory_order_release, //success: write top_
            std::memory_order_relaxed // failure: read new top
        )) {}
    }
};


/*
wait-free
*/ 

class registy_mutex{
    std::mutex mtx_;
    std::atomic<size_t> count_{0};
public:
    size_t read(){  return count_.load(std::memory_order_acquire); }
    void increment(size_t i){  count_.fetch_add(i, std::memory_order_release); }
};

