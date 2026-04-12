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
    // Helper function to find the maximum sum that crosses the midpoint
    int maxCrossingSum(vector<int>& nums, int left, int mid, int right) {
        int sum = 0;
        int left_sum = INT_MIN;

        // Include elements from mid down to left
        for (int i = mid; i >= left; i--) {
            sum += nums[i];
            if (sum > left_sum)
                left_sum = sum;
        }

        sum = 0;
        int right_sum = INT_MIN;

        // Include elements from mid+1 up to right
        for (int i = mid + 1; i <= right; i++) {
            sum += nums[i];
            if (sum > right_sum)
                right_sum = sum;
        }

        // Return sum of elements on left and right of mid
        return left_sum + right_sum;
    }

    int solve(vector<int>& nums, int left, int right) {
        // Base Case: Only one element
        if (left == right) {
            return nums[left];
        }

        int mid = left + (right - left) / 2;

        // Return the maximum of:
        // 1. Max subarray sum in left half
        // 2. Max subarray sum in right half
        // 3. Max subarray sum crossing the midpoint
        return max({
            solve(nums, left, mid),
            solve(nums, mid + 1, right),
            maxCrossingSum(nums, left, mid, right)
        });
    }

    int maxSubArray(vector<int>& nums) {
        return solve(nums, 0, nums.size() - 1);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << sol.maxSubArray(nums) << endl; // Output: 6
    return 0;
}

