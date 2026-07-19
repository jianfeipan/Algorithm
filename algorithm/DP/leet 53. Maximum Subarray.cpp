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
            minPrefixSumSofar = min(minPrefixSumSofar, prefixSum);
            
            maxSubArray = max(maxSubArray, prefixSum - minPrefixSumSofar);
        }
        
        return maxSubArray;
    }
};


#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution_devide_conquer {
public:
    int maxSubArray(vector<int>& nums) {
        return dfs(nums, 0, nums.size() - 1);
    }

private:
    int dfs(vector<int>& nums, int l, int r) {
        if (l > r) return INT_MIN;

        int m = (l + r) >> 1;
        // try to find the max sum including middle
        int max_sum_left = 0;
        {// from m, extend to left
            int sum = 0;
            for (int i = m - 1; i >= l; --i) {
                sum += nums[i];
                max_sum_left = max(max_sum_left, sum);
            }
        }
        int max_sum_right = 0;
        {// from m, extend to left
            int sum = 0;
            for (int i = m + 1; i <= r; ++i) {
                sum += nums[i];
                max_sum_right = max(max_sum_right, sum);
            }
        }

        
        
        return max(dfs(nums, l, m - 1),// max live on the left 
                   max(dfs(nums, m + 1, r), // max live on the right 
                       max_sum_left + nums[m] + max_sum_right));// max live cross the m 
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << sol.maxSubArray(nums) << endl; // Output: 6
    return 0;
}

