class Solution {
    /*
    first unordered map to count
    then two way to sort : 
      1 TreeMap : N(NlogN) 
      2 PriorityQueue : N(KlongN) we only do K pop and heapifiy
    
    
    */
    struct comp
    {
        bool operator() (const pair<int, string>& left, const pair<int, string> & right)
        {
            if(left.first == right.first)
            {
                return left.second>right.second;
            }
            else
            {
                return left.first<right.first;
            }
            
        }
    };
        
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        //_bucket_sort_extra_memory: first map for count, second map for sorting
        map<string, int> counts;
        for(const string & s : words)
        {
            counts[s]++;
        }
        
        //Heap 
        priority_queue<pair<int, string>, vector<pair<int,string>>, comp> pQueue;
        
        for(auto kv : counts)
        {
            pQueue.push(make_pair(kv.second, kv.first));
        }
        
        
        vector<string> result;
        result.reserve(k);
        
        while(result.size() < k && !pQueue.empty())
        {
            result.push_back(pQueue.top().second);
            pQueue.pop();
        }
        
        
        return result;
    }
    
    
    vector<string> topKFrequent_tree_Map(vector<string>& words, int k) {
                //_bucket_sort_extra_memory: first map for count, second map for sorting
        map<string, int> counts;
        for(const string & s : words)
        {
            counts[s]++;
        }
        
        map<int, set<string>> bucket;
        
        for(auto kv : counts)
        {
            bucket[kv.second].insert(kv.first);
        }
        
        
        vector<string> result;
        result.reserve(k);
        for(auto it = bucket.rbegin(); it!=bucket.rend(); ++it)
        {
            if(!it->second.empty())
            {
                for(const auto &  s : it->second)
                {
                    result.push_back(s);
                    if(result.size() == k)
                        return result;
                }
            }
        }
        
        return result;
    }
};
