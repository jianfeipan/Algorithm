template<typename K>
class LFUPolicy{
private:
    using Freq = int;
    using It = typename list<K>::iterator;
    unordered_map<K, Freq> freq;
    unordered_map<K, It> order;
    map<int, list<K>> keysByFreq;
public:
    K getLFU(){
        if(keysByFreq.empty()) return -1; //empty
        return keysByFreq.begin()->second.front();//LRU
    }

    void touch(K key){
        auto& frequency = freq[key];
        auto it = order.find(key);
        if(it != order.end()){
            auto& pos = it->second;
            keysByFreq[frequency].erase(pos);
            if(keysByFreq[frequency].empty())
                keysByFreq.erase(frequency);
        }
        
        ++frequency;
        keysByFreq[frequency].push_back(key);
        order[key] = prev(keysByFreq[frequency].end());
    }

    void remove(K key){
        auto it = freq.find(key);
        if(it!=freq.end()){
            auto frequency = it->second;

            auto orderIt = order.find(key);
            if(orderIt != order.end()){
                auto& pos = orderIt->second;
                keysByFreq[frequency].erase(pos);
                if(keysByFreq[frequency].empty())
                    keysByFreq.erase(frequency);
                order.erase(orderIt);
            }
            freq.erase(it);
        }
            
        
    }
};

class LFUCache {
private:
    unordered_map<int, int> data;
    int capacity;
    LFUPolicy<int> policy;

public:
    LFUCache(int _capacity):capacity(_capacity), policy() {
    }
    
    int get(int key) {
        if(!data.count(key)) return -1;

        policy.touch(key);
        return data[key];
    }
    
    void put(int key, int value) {
        if(capacity == 0) return;
        auto it = data.find(key);
        if(it!=data.end()){// update
            data[key] = value;
            policy.touch(key);
        }else{ // insert
            if(data.size() == capacity){
                auto lfuKey = policy.getLFU();
                data.erase(lfuKey);
                policy.remove(lfuKey);
            } 
            data[key] = value;
            policy.touch(key);
        }        
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
