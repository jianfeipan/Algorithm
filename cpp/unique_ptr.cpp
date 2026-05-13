namespace my{

template<typename T>
class unique_ptr{
private:
    T* data_;

public:
    unique_ptr(T* data) : data_(data){}
    ~unique_ptr(){ delete data_; }

    // no copy
    unique_ptr(const unique_ptr& ) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // move
    unique_ptr(unique_ptr&& that){
        data_ = that.data_;
        that.data_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& that){
        if(this!=that){
            reset();
            this->data_ = that->data_;
            that->data_ = nullptr;
        }
    }

    // observer
    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    T* get() const { return data_; }

    // setter
    T* release(){
        auto* res = data_;
        data_=nullptr;
        return res;
    }

    void reset(){
        if(data_){
            delete data_;
            data_ = nullptr;
        }
    }
};

}