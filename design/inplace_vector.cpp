// Implement `std::inplace_vector`

#include <cstddef>
#include <iostream>
#include <memory>

namespace qrt {

template <typename T, std::size_t Capacity>
class inplace_vector{
private:
    char _data[Capacity*sizeof(T)];
    int _size;
    
    T* _nextLocation(){
        return (T*)(_data + sizeof(T) * _size);
    }
public:
    inplace_vector():_size(0){
    }
    
    size_t capacity(){
        return Capacity;
    }

    size_t size(){
        return _size;
    }

    template<typename... Args>
    void emplace_back(Args...args){
        std::construct_at(_nextLocation(), args...);
        ++_size;
    }
    
    void push_back(const T& data){
        std::construct_at(_nextLocation(), data);
        ++_size;
    }
    
    T* begin(){
        return (T*)_data;
    }
    
    T* end(){
        return _nextLocation();
    }
};
} // namespace qrt

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
    qrt::inplace_vector<Widget, 8> vi;
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
