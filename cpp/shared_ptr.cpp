namespace my {

template<typename T>
class shared_ptr {
private:
    T* data_ = nullptr;
    size_t* counter_ = nullptr; // In real life, use std::atomic<size_t>

    void release() {
        if (counter_) {
            (*counter_)--;
            if (*counter_ == 0) {
                delete data_;
                delete counter_;
            }
            data_ = nullptr;
            counter_ = nullptr;
        }
    }

public:
    // Constructor
    explicit shared_ptr(T* data = nullptr) : data_(data) {
        if (data_) {
            counter_ = new size_t(1);
        }
    }

    // Destructor
    ~shared_ptr() {
        release();
    }

    // Copy Constructor
    shared_ptr(const shared_ptr& that) : data_(that.data_), counter_(that.counter_) {
        if (counter_) {
            ++(*counter_);
        }
    }

    // Copy Assignment
    shared_ptr& operator=(const shared_ptr& that) {
        if (this != &that) {
            release(); // Clean up current resource first!
            data_ = that.data_;
            counter_ = that.counter_;
            if (counter_) {
                ++(*counter_);
            }
        }
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
            release(); // Clean up current resource first!
            data_ = that.data_;
            counter_ = that.counter_;
            that.data_ = nullptr;
            that.counter_ = nullptr;
        }
        return *this;
    }

    // Observers
    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    T* get() const { return data_; }
    size_t use_count() const { return counter_ ? *counter_ : 0; }
    explicit operator bool() const { return data_ != nullptr; }

    void reset(T* data = nullptr) {
        release();
        if (data) {
            data_ = data;
            counter_ = new size_t(1);
        }
    }
};

} // namespace my
