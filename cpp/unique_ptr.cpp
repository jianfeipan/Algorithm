namespace my {

template<typename T>
class unique_ptr {
private:
    T* data_;

public:
    // Marked explicit to prevent accidental conversions
    explicit unique_ptr(T* data = nullptr) : data_(data) {}

    ~unique_ptr() { delete data_; }

    // No copy
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Move Constructor
    unique_ptr(unique_ptr&& that) noexcept : data_(that.data_) {
        that.data_ = nullptr;
    }

    // Move Assignment
    unique_ptr& operator=(unique_ptr&& that) noexcept {
        if (this != &that) { // Fix: compare addresses
            reset();
            this->data_ = that.data_; // Fix: access member via dot
            that.data_ = nullptr;
        }
        return *this; // Fix: return reference
    }

    // Observers & Operator Overloads
    T* get() const { return data_; }
    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    explicit operator bool() const { return data_ != nullptr; }

    T* release() {
        T* res = data_;
        data_ = nullptr;
        return res;
    }

    void reset(T* p = nullptr) {
        if (data_ != p) {
            delete data_;
            data_ = p;
        }
    }
};

}