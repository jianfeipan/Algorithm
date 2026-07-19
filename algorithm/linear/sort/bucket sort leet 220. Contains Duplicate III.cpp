class Solution {
public:
     bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) 
     {
        return containsNearbyAlmostDuplicate_bucket(nums, k, t);  
     }

    
    
     bool containsNearbyAlmostDuplicate_bucket(vector<int>& nums, int k, int t) {
        int n = nums.size();
        
        if(n == 0 || k < 0  || t < 0) return false;
        
        unordered_map<int,int> buckets;//bucketKey value
        
        for(int i=0; i<n; ++i) {
            int bucketKey = nums[i] / ((long)t + 1);
            /* we can use this to transform the contraint of |a-b| <=t to  |a/(1+t)-b/(1+t)| <= t/t+1
                
                with t > 0; we have t/t+1 < 1
                so if we have a/(1+t) == b/(1+t), so we have |a-b| <=t
                
                if we want to make sur |a-b|<=t, with int floor, we need to make sure : 
                    | a/(1+t) - b/(1+t) | == 0 or 1
            */
            if(nums[i] < 0) --bucketKey;
			// For negative numbers, we need to decrement bucket by 1
			// to ensure floor division.
			// For example, -1/2 = 0 but -1 should be put in Bucket[-1].
			// Therefore, decrement by 1.
            
            if(buckets.find(bucketKey) != buckets.end()) return true;
            else {
                buckets[bucketKey] = nums[i];
                
                //with approche  |a/(1+t)-b/(1+t)| = 0 or 1
                if(buckets.count(bucketKey-1) && (long) nums[i] - buckets[bucketKey-1] <= t) return true;
                if(buckets.count(bucketKey+1) && (long) buckets[bucketKey+1] - nums[i] <= t) return true;
                
                if(buckets.size() > k) {
                    int key_to_remove = nums[i-k] / ((long)t + 1);
                    
                    if(nums[i-k] < 0) --key_to_remove;
                    
                    buckets.erase(key_to_remove);
                }
            }
        }
        
        return false;
    }
    

    bool containsNearbyAlmostDuplicate_brute_force(vector<int>& nums, int k, int t) {
        for(size_t from = 0; from<nums.size(); ++from)
        {
            for(size_t to = from+1; to<=from + k && to<nums.size(); ++to )//abs (i - j) < k
            {
                //cout<<nums[from]<<" - "<<nums[to]<<endl;
                if(abs((long)nums[from] - nums[to])<=t)//INT_MAX prblem
                    return true;
            }
        }
        return false;
    }
};
