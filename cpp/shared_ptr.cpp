#include <atomic>
#include <utility>

namespace my {

template<typename T>
class shared_ptr {
private:
    T* data_ = nullptr;
    std::atomic<size_t>* counter_ = nullptr; 

    void release() {
        if (counter_) {
            // fetch_sub returns the value BEFORE decrement
            if (counter_->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete data_;
                delete counter_;
            }
            data_ = nullptr;
            counter_ = nullptr;
        }
    }

public:
    explicit shared_ptr(T* data = nullptr) : data_(data) {
        if (data_) {
            counter_ = new std::atomic<size_t>(1);
        }
    }

    ~shared_ptr() {
        release();
    }

    // Copy Constructor
    shared_ptr(const shared_ptr& that) : data_(that.data_), counter_(that.counter_) {
        if (counter_) {
            counter_->fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Copy Assignment (Using Copy-and-Swap idiom for safety)
    shared_ptr& operator=(const shared_ptr& that) {
        if (this != &that) {
            shared_ptr tmp(that); // Use copy constructor (increments counter)
            swap(*this, tmp);     // Swap internals
        }                         // tmp goes out of scope (decrements old counter)
        return *this;
    }

    // Move Constructor
    shared_ptr(shared_ptr&& that) noexcept : data_(that.data_), counter_(that.counter_) {
        that.data_ = nullptr;
        that.counter_ = nullptr;
    }

    // Move Assignment
    shared_ptr& operator=(shared_ptr&& that) noexcept {
        if (this != &that) {
            release();
            data_ = that.data_;
            counter_ = that.counter_;
            that.data_ = nullptr;
            that.counter_ = nullptr;
        }
        return *this;
    }

    // Hidden friend: not a member function: calling swap(this, that)
    friend void swap(shared_ptr& a, shared_ptr& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.counter_, b.counter_);
    }

    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    size_t use_count() const { return counter_ ? counter_->load() : 0; }
};

} // namespace my