/*
Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:

0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 

Example 1:

Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
Output: 2
Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
Example 2:

Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
Output: 1

*/


class Solution {

/*
fact: 
    reaturn number of tuples instead of bool means we ned to search all combinations: n^4

idea:
    DP: take "nums1[0]" -> find "-nums1[0]" with nums2,nums3,nums4
    cache
*/
private:
    int dp(int target,  const vector<vector<int>>  & nums, int numbVectorUsed, vector<unordered_map<int, int>> & cache)
    {
        if(numbVectorUsed == nums.size()) return target ==0 ? 1 : 0;

        auto it = cache[numbVectorUsed].find(target); 
        if(it!=cache[numbVectorUsed].end()) return it->second;

        int count = 0;
        const auto & currentArray = nums[numbVectorUsed];
        for (int i = 0; i < currentArray.size(); ++i)
        {
            count += dp(target - currentArray[i], nums, numbVectorUsed + 1, cache);
        }
        cache[numbVectorUsed][target] = count;
        return count;

    }


public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) 
    {
        vector<vector<int>> nums({nums1, nums2, nums3, nums4});

        vector<unordered_map<int, int>> cache(nums.size(), unordered_map<int, int>());

        return  dp(0/*target*/,nums,  0/*from  vector 0*/, cache);     
        
    }
};
