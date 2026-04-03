class Solution {
public:
    int firstMissingPositive_extra_vector(vector<int>& nums) 
    {
        vector<bool> bucket(nums.size(), false);// space O(n)!!
        
        for(const auto & num : nums)
        {
            if(0 < num && num <= bucket.size()) bucket[num-1] = true;
        }
        
        
        for(int i = 0; i< bucket.size(); ++i)
        {
            if(!bucket[i]) return i+1;
        }
        
        return bucket.size()+1;
    }
    // 0  1  2   3
    //[3, 4, -1, 1]
    // i
    // nums[3] = 1
    // we should be able to do swap in place to reach space O(1)
    int firstMissingPositive(vector<int>& nums){
        const auto& n = nums.size();
        for(int i=0; i<n; ++i){
            // nums[i] should be the number i+1
            while(nums[i] != i+1 // already good position
                && nums[i] > 0   // index valid
                && nums[i]<=n    // index valid
                && nums[i]!= nums[nums[i]-1]) { // swap makes sens: 
                // no worries if we have repeated 2s for exmaple, 
                //they will  be placed at the first unmactched place
                swap(nums[i], nums[nums[i]-1]);
            }
            // this will result to at this i, we have the right number i+1, or have an invalid number
        }
        // now we have allnumbers at their place should be : nums[i] = i+1 excapt the invalid number 0 or -1
        for(int i=0; i<n; ++i){
            if(nums[i] != i+1) return i+1;
        }

        return n+1;
    }

};
