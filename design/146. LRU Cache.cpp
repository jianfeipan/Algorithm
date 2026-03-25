/*Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4*/

class LRUCache {

/*
fact: 
    1 k-v cache , no order in keys 
    2 least Recently Used 
        we need counts of usage 
        we need a container for order
        we need to maintain the size, remove the least Rencent used.

idea:
    1 --> unordered_map
    2 LRU
        2.1: <key, < value, count  > >
        2.2  operations we need on this container  
                add --> new added is most recently used
                move --> if the node is already used, move it to the most recently used position--> random access(make use of the map)
                remove --> remove always the least recent used --> tail
            --> std::list
        2.3 counter of capacity


*/
/*
last recent used:
a map for the key value cache
    -> unordered_map
    -> we need to use key to access the list iterator inorder to move it
a structure with order to keep track the used order
    -> move node from one position to another -> List

*/

class LRUCache {
private:
    unordered_map<int, list<pair<int, int>>::iterator> m_data;
    list<pair<int, int>> m_order; // key value: we need key to evict map
    int m_capacity;
public:
    LRUCache(int capacity): m_capacity(capacity) {

    }

    int get(int key) {
        if(m_data.count(key)){
            auto hit = m_data[key];
            //m_order.splice(m_order.begin(), m_order, hit); // slice is change the poitner, more efficient than create copy remove
            m_order.splice(m_order.begin(), m_order, hit);
            // m_order.push_front({hit->first, hit->second});
            // m_order.erase(hit);
            return m_order.front().second;
        }

        else
            return -1;
    }

    void put(int key, int value) {
        if(m_data.count(key)){
            auto hit = m_data[key];
            m_order.splice(m_order.begin(), m_order, hit); // slice is change the poitner, more efficient than create copy remove
            hit->second = value;// update
        }else{
            if(m_data.size() == m_capacity){
                // eviction: the last in the order list
                auto key =  m_order.back().first;
                m_data.erase(key);
                m_order.pop_back();
            }
            m_order.push_front({key, value});
            m_data[key] = m_order.begin();

        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
