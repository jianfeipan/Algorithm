class RandomizedSet {
public:
    RandomizedSet() {}
    
    bool insert(int val)
    {
        if(_valToIndex.count(val) != 0) return false;
        
        _valToIndex[val] = _values.size();
        _values.push_back(val);
        return true;
    }
    
    bool remove(int val)
    {
        if(_valToIndex.count(val) == 0) return false;
        
        const int indexToRemove = _valToIndex[val];
       
        _values[indexToRemove] = _values.back();//use swap back then pop back to remove : we don't need an order, just random access
        _values.pop_back();
        
        _valToIndex[ _values[indexToRemove]] = indexToRemove;
        
        _valToIndex.erase(val);
        return true;
    }
    
    int getRandom() 
    {
        return _values[random()%_values.size()];
    }
    
private:
    unordered_map<int , size_t> _valToIndex;
    vector<int> _values;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
