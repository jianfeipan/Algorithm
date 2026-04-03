class Solution_bottom_up_DP {
    
    /*
    Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

range_sum = prefixSum_j- prefixSum_i 
 we want max range sum, which means we need to be the min
 --> SIMILAR TOT THE STOCK PRICE
 so in one pass: 
     we compute the current prefixSum
     we use current_prefixSum - minPrefixSumSoFar to try the max
     we updat ethe minPrefixSumSoFar
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {//cumulated sum 
        int prefixSum = 0;
        int minPrefixSumSofar = 0;
        int maxSubArray = INT_MIN;
        
        for(int i = 0; i<nums.size(); ++i)
        {
            prefixSum = prefixSum + nums[i];
            maxSubArray = max(maxSubArray, prefixSum - minPrefixSumSofar);
            minPrefixSumSofar = min(minPrefixSumSofar, prefixSum);
        }
        
        return maxSubArray;
    }
};
};

