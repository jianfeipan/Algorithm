class BrowserHistory {
public:
    BrowserHistory(string homepage) :
    _order(),
    _current()
    {
        _order.push_front(homepage);
        _current = _order.begin();
    }
    
    void visit(string url) 
    {
        _order.erase(_order.begin(), _current);
        
        _order.push_front(url);
        _current = _order.begin();
    }
    
    string back(int steps) 
    {
        auto it = _current;
        
        while(steps-->0 && it!=_order.end()) ++it;
        
        if(steps>0 || it==_order.end()) _current =  --_order.end();
        else _current = it;
        
        return *_current;
    }
    
    string forward(int steps) 
    {
        auto it = _current;
        
        while(steps-->0 && it!=_order.begin()) --it;
        
        if(steps>0 || it==_order.begin()) _current =  _order.begin();
        else _current = it;
        
        return *_current;
    }
    
private:
    list<string> _order;
    list<string>::iterator _current;
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
