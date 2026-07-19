class MinStack {
public:
    MinStack() {
        
    }
    
    void push(int val) 
    {
        if(_min.empty() || val<=_min.top()) _min.push(val);
        _data.push(val);
    }
    
    void pop()
    {
        if(_min.top() == _data.top())
            _min.pop();
        _data.pop();
    }
    
    int top() 
    {
        return _data.top();
    }
    
    int getMin() {
        return _min.top();
    }
private:
    stack<int> _data;
    stack<int> _min;
    
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
