class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        return twoSum_note_then_check(nums, target);
    }
    
private:
    
    vector<int> twoSum_hash_map_check(vector<int> nums, int target) 
    {
        unordered_map<int, int> valueToIndex;
        for(int i = 0; i<nums.size(); ++i)
        {
            const int lookingFor = target - nums[i];
            if(valueToIndex.count(lookingFor))
                return {valueToIndex[lookingFor], i};
            valueToIndex[nums[i]] = i;
        }
        return {};//or throw an exception "not found" 
    }
    
    vector<int> twoSum_sorted_two_pinter(vector<int> nums, int target) 
    {
        map<int, int> valueToIndex;
        for(size_t i = 0; i<nums.size(); ++i)
            valueToIndex[nums[i]] = i;
        
        sort(nums.begin(), nums.end());
        size_t left = 0;
        size_t right = nums.size()-1;
        while(left<right)
        {
            const int sum = nums[left] + nums[right];
            if(sum == target) return {valueToIndex[nums[left]], valueToIndex[nums[right]]};
            else if(sum > target) --right;
            else ++left;
        }
        
        return {};//or throw an exception "not found" 

    }

    vector<int> twoSum_brute_force(const vector<int>& nums, int target) 
    {
        for(size_t i = 0; i< nums.size(); ++i)
            for(size_t j = i+1; j< nums.size(); ++j)
                if(nums[i] + nums[j] == target) return {static_cast<int>(i), static_cast<int>(j)};
        return {};//throw exception "not found"
                
    }
};
