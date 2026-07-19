/*

Given a stream of 'query name' and 'execution time', 
design a data structure that can return the k fastest query name. 
If a new entry's query name is already seen, replace the old execution time with the new one.
ex stream:
query1, 10s
query2, 30s
query3, 20s
query1, 20s
class TopK:
def update(query, time):
def get(k):

*/

class TopKRecord
{

public:
    TopK(int capacity)
    {
        _capacity = capacity;
    }
    
    int readRecord(const String & key)
    {
        auto it = _cache.find(key);
        if(it!=_cache.end())
        {
            return it->second;
        }
        else
        {
            return -1;
        }
    }
    
    int putRecord(const String & key, int value)
    {
        auto it = _cache.find(key);
        if(it!=_cache.end())
        {
            
        }
        else
        {
           auto it = _executionTimes.insert({value, key});
            _cache[key] = it;
            if(_capacity>0)
            {
                --_capacity;
            }
            else
            {
                const string & keyToRemove = _executionTimes.begin();
                auto it = _cache.find(keyToRemove);
                _cache.erase(it);
                _executionTimes.erase( _executionTimes.begin());
            }
            
        }
    }
    
private:
    unordered_map<string, priority_queue<pair<int, string>>::iterator> _cache;
    priority_queue<pair<int, string>> _executionTimes;
    int _capacity;
  
}
