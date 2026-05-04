// Implement `std::inplace_vector`

#include <cstddef>
#include <iostream>
#include <memory>

namespace my {

template <typename T, std::size_t Capacity>
class inplace_vector {
private:
    alignas(T) char _data[Capacity * sizeof(T)];
    std::size_t _size = 0;

    T* data_ptr() { return reinterpret_cast<T*>(_data); }

public:
    inplace_vector() : _size(0) {}

    // CRITICAL: Clean up resources
    ~inplace_vector() {
        std::destroy(begin(), end());
    }

    size_t size() const { return _size; }
    size_t capacity() const { return Capacity; }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (_size >= Capacity) throw std::out_of_range("Capacity exceeded");
        
        std::construct_at(data_ptr() + _size, std::forward<Args>(args)...);
        ++_size;
    }

    void push_back(const T& value) { emplace_back(value); }
    void push_back(T&& value) { emplace_back(std::move(value)); }

    T* begin() { return data_ptr(); }
    T* end() { return data_ptr() + _size; }
    
    // Const versions for iteration
    const T* begin() const { return reinterpret_cast<const T*>(_data); }
    const T* end() const { return reinterpret_cast<const T*>(_data) + _size; }
};
} // namespace my

class Widget {
  int _val = 0;

 public:
  Widget() { std::cout << "Widget default ctor\n"; }
  Widget(int val) : _val(val) { std::cout << "Widget(" << _val << ")\n"; }
  ~Widget() { std::cout << "~Widget(" << _val << ")\n"; }

  Widget(Widget&& other) {
    std::cout << "Widget move ctor from " << other._val
              << '\n';
    _val = other._val;
  }
  Widget(const Widget& other) : _val(other._val) {
    std::cout << "Widget copy ctor from " << other._val
              << '\n';
    _val = other._val;
  }

  Widget& operator=(Widget&& other) {
    std::cout << "Widget move assignment from " << other._val << " to " << _val
              << '\n';
    _val = other._val;
    return *this;
  }
  Widget& operator=(const Widget& other) {
    std::cout << "Widget copy assignment from " << other._val << " to " << _val
              << '\n';
    _val = other._val;
    return *this;
  }

  int value() const { return _val; }
};

int main() {
    my::inplace_vector<Widget, 8> vi;
    vi.emplace_back();
    vi.emplace_back(42);
    vi.push_back(Widget(5));


    std::cout << "Contents: [";
    for(const auto& w : vi) {
        std::cout << "Widget(" << w.value() << "), ";
    }
    std::cout << "]\n";
    std::cout << "Size: " << vi.size() << '\n';
    std::cout << "Capacity: " << vi.capacity() << '\n';
}
