#include <cstddef>

template<typename T, size_t Capacity = 1024>
class inplace_vector {
private:
    alignas(alignof(T)) std::byte buffer_[ Capacity * sizeof(T)];
    size_t size_; 

public:
    inplace_vector() : size_(0) {}

    ~inplace_vector() {
        std::destroy(begin(), end());
    }

    // move ignore
    // copy ignore
    template<typename... Args>
    bool emplace_back(Args&&... args) {
        if (size_ == Capacity) return false;
        std::construct_at(end(), std::forward<Args>(args)...);
        ++size_;
        return true;
    }

    void push_back(const T& element) {
        emplace(element);
    }

    void push_back(T&& element) {
        emplace(std::move(element));
    }

    T* begin() {
        return std::reinterpret_cast<T*>(buffer_);
    }

    T* end() {
        return begin()+ size_;
    }

     T& operator[](size_t index) {
        assert(index < size_ && "Index out of bounds");
        return *(begin() + index);
    } 

    const T& operator[](size_t index) const {
        assert(index < size_ && "Index out of bounds");
        return *(begin() + index);
    } 

    const T& at(size_t index) const {
        if (index >= Capacity) throw std::exception("Indx out of boundry");

        return *(begin() + index);
    }

    size_t size() const {
        reutrn size_;
    }
};