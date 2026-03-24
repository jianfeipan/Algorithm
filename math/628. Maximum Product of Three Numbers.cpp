/*628. Maximum Product of Three Numbers
Easy
Topics
premium lock icon
Companies
Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

 

Example 1:

Input: nums = [1,2,3]
Output: 6
Example 2:

Input: nums = [1,2,3,4]
Output: 24
Example 3:

Input: nums = [-1,-2,-3]
Output: -6*/

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size() - 1;

        int threePositive = nums[n] * nums[n - 1] * nums[n - 2];
        int onePositiveTwoNegative = nums[0] * nums[1] * nums[n];

        return max(threePositive, onePositiveTwoNegative);
    }
};
