//Solution 01:
class RandomizedCollection {
private:
    vector<pair<int, int>> data;
    unordered_map<int, vector<int>> index;
public:
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        const bool present = index.count(val);

        index[val].push_back(data.size());
        data.push_back(make_pair(val, index[val].size()-1));

        return !present;
    }
    
    bool remove(int val) {
        if(!index.count(val)) return false;
        // swap to back and pop_back
        auto toRemove = index[val].back();
        auto last = data.back();
        auto lastValue = last.first;
        auto lastIndex = last.second;
        index[lastValue][lastIndex] = toRemove;
        data[toRemove] = last;

        index[val].pop_back();
        if(index[val].empty())
            index.erase(val);
        data.pop_back();

        return true;         
    }
    
    int getRandom() {
        return data[rand()%data.size()].first;
    }
};

/* * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
