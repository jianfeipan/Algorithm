class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //_bucket_sort_extra_memory: first map for count, second map for sorting
        map<int, int> counts;
        for(int i : nums)
        {
            counts[i]++;
        }
        
        map<int, vector<int>> bucket;
        
        for(auto kv : counts)
        {
            bucket[kv.second].push_back(kv.first);
        }
        
        
        vector<int> result;
        result.reserve(k);
        for(auto it = bucket.rbegin(); it!=bucket.rend(); ++it)
        {
            if(!it->second.empty())
            {
                for(int i : it->second)
                {
                    result.push_back(i);
                    if(result.size() == k)
                        return result;
                }
            }
        }
        
        return result;
    }
    

    
    
    vector<int> topKFrequent_quickSort_in_place_time_limit_exceeded(vector<int>& nums, int k) {
        //Idea: use map to do frequent count, then get the first k keys with biggest counts 
        map<int, int> counts;
        for(int i : nums)
        {
            counts[i]++;
        }
        
        vector<int> result;
        result.reserve(counts.size());
        
        //counts.keys()
        for(auto kv : counts)
        {
            result.push_back(kv.first);
        }
        //O(NlogN)
        sort(result.begin(), result.end(), [counts](int left, int right){
            auto leftIt = counts.find(left);
            auto rightIt = counts.find(right);
            return leftIt->second > rightIt->second;
        } );
        
            
        return vector<int>(result.begin(),result.begin() + k);
    }
};
