#include <cstddef>
#include <cassert>

template<typename T>
struct Control {
    T* ptr_ = nullptr;
    size_t ref_count_ = 0;
    size_t weak_count_ = 0;
};

// Forward declaration
template<typename T> class WeakPtr;

template<typename T>
class SharedPtr {
private:
    Control<T>* ctrl_ = nullptr;

    // Private constructor allowing WeakPtr::lock() to build a SharedPtr efficiently
    SharedPtr(Control<T>* ctrl) : ctrl_(ctrl) {
        if (ctrl_) {
            ++(ctrl_->ref_count_);
        }
    }

public:
    // Default constructor for empty shared_ptrs
    SharedPtr() : ctrl_(nullptr) {}

    SharedPtr(T* ptr) {
        if (ptr) {
            ctrl_ = new Control<T>{ptr, 1, 0};
        }
    }

    ~SharedPtr() {
        release();
    }

    // Move Constructor
    SharedPtr(SharedPtr&& that) noexcept : ctrl_(that.ctrl_) {
        that.ctrl_ = nullptr; // Steal ownership, ensure 'that' won't delete it
    }

    // Move Assignment
    SharedPtr& operator=(SharedPtr&& that) noexcept {
        if (this != &that) {
            release();           // Drop our current resource
            ctrl_ = that.ctrl_;  // Steal the new one
            that.ctrl_ = nullptr; // Clear the source
        }
        return *this;
    }

    // Copy Constructor
    SharedPtr(const SharedPtr& that) : ctrl_(that.ctrl_) {
        if (ctrl_) {
            ++(ctrl_->ref_count_);
        }
    }

    // Copy Assignment
    SharedPtr& operator=(const SharedPtr& that) {
        if (this != &that) {
            release();
            ctrl_ = that.ctrl_;
            if (ctrl_) {
                ++(ctrl_->ref_count_);
            }
        }
        return *this;
    }

    void release() {
        if (ctrl_) {
            --(ctrl_->ref_count_);
            if (ctrl_->ref_count_ == 0) {
                delete ctrl_->ptr_;
                ctrl_->ptr_ = nullptr;
            }
            
            if (ctrl_->ref_count_ == 0 && ctrl_->weak_count_ == 0) {
                delete ctrl_;
            }
            ctrl_ = nullptr;
        }
    }

    // Observers
    T* operator->() const {
        return ctrl_ ? ctrl_->ptr_ : nullptr;
    }

    T& operator*() const {
        //assert(ctrl_ && ctrl_->ptr_ && "Dereferencing a null SharedPtr");
        return *(ctrl_->ptr_); 
    }

    // Correct template friend syntax
    friend class WeakPtr<T>;
};

template<typename T>
class WeakPtr {
private:
    Control<T>* ctrl_ = nullptr;

public:
    WeakPtr() : ctrl_(nullptr) {}

    WeakPtr(const SharedPtr<T>& shared) : ctrl_(shared.ctrl_) { 
        if (ctrl_) {
            ++(ctrl_->weak_count);
        }
    }

    ~WeakPtr() {
        clean();
    }

    // WeakPtr should also be copyable!
    WeakPtr(const WeakPtr& that) : ctrl_(that.ctrl_) {
        if (ctrl_) {
            ++(ctrl_->weak_count);
        }
    }

    WeakPtr& operator=(const WeakPtr& that) {
        if (this != &that) {
            clean();
            ctrl_ = that.ctrl_;
            if (ctrl_) {
                ++(ctrl_->weak_count);
            }
        }
        return *this;
    }

    WeakPtr(WeakPtr&&) = delete;
    WeakPtr& operator=(WeakPtr&&) = delete;

    // uses the private SharedPtr constructor safely
    SharedPtr<T> lock() const {
        if (ctrl_ && ctrl_->ref_count_ > 0) {
            return SharedPtr<T>(ctrl_); 
        }
        return SharedPtr<T>(); // Returns an empty SharedPtr if expired
    }

private:
    void clean() {
        if (ctrl_) {
            --(ctrl_->weak_count);
            if (ctrl_->ref_count_ == 0 && ctrl_->weak_count_ == 0) {
                delete ctrl_;
            }
            ctrl_ = nullptr;
        }
    }
};
