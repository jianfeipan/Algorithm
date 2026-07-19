class Solution {
    
    /*
    Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that |nums[i] - nums[j]| == k.

The value of |x| is defined as:

x if x >= 0.
-x if x < 0.
 

Example 1:

Input: nums = [1,2,2,1], k = 1
Output: 4
Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100
1 <= k <= 99
    */
public:
    int countKDifference(vector<int>& nums, int k) 
    {
        return countKDifference_vector_cout(nums, k);
    }
private:
    
     int countKDifference_vector_cout(vector<int>& nums, int k) //O(N) -->very smart solution
    {
        if(nums.empty()) return -1;//thow exception
     
        int count = 0;
        
         //1 <= nums[i] <= 100!!!!!!! bitmap instead of map
        int diagram[101] = {};
        for(int num : nums) ++diagram[num]; 
        
        for(int i = 1; i <= 100; ++i)
        {
            if(i - k>=0 && i-k<=100)
                count += diagram[i] * diagram[i - k];
        }
        
        return count;
    }
    
    int countKDifference_map_cout_two_pointer(vector<int>& nums, int k) //O(N)
    {
        if(nums.empty()) return -1;//thow exception
     
        int count = 0;
        
        map<int, size_t> orderedNums;
        for(int num : nums) ++orderedNums[num]; 
        
        vector<int> uniqueOrderedNums;
        for(auto[key, value] : orderedNums)
            uniqueOrderedNums.push_back(key);
        
        size_t left = 0;
        size_t right = 1;
        while(right<uniqueOrderedNums.size() && left<uniqueOrderedNums.size())
        {

            if(uniqueOrderedNums[right] - uniqueOrderedNums[left] == k)
            {
                count+=orderedNums[uniqueOrderedNums[left]] * orderedNums[uniqueOrderedNums[right]];
                ++left;++right;
            }
            else if(uniqueOrderedNums[right] - uniqueOrderedNums[left] < k) ++right;
            else ++left;
        }
        
        return count;
    }
    
    int countKDifference_brute_force(vector<int>& nums, int k) 
    {
        int count = 0;
        for(size_t i = 0; i<nums.size();++i)
            for(size_t j = i+1; j<nums.size(); ++j)
                if(abs(nums[i] - nums[j]) == k) ++count;
        return count;
    }

};
