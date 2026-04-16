/*
2009. Minimum Number of Operations to Make Array Continuous

You are given an integer array nums. In one operation, you can replace any element in nums with any integer.

nums is considered continuous if both of the following conditions are fulfilled:

All elements in nums are unique.
The difference between the maximum element and the minimum element in nums equals nums.length - 1.
For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.

Return the minimum number of operations to make nums continuous.

 

Example 1:

Input: nums = [4,2,5,3]
Output: 0
Explanation: nums is already continuous.
Example 2:

Input: nums = [1,2,3,5,6]
Output: 1
Explanation: One possible solution is to change the last element to 4.
The resulting array is [1,2,3,5,4], which is continuous.
Example 3:

Input: nums = [1,10,100,1000]
Output: 3
Explanation: One possible solution is to:
- Change the second element to 2.
- Change the third element to 3.
- Change the fourth element to 4.
The resulting array is [1,2,3,4], which is continuous.
*/

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int minOperations = n;

        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int nUniq = nums.size();

        int right = 0;

        for (int left = 0; left < nUniq; left++) {
            // for every left
            // since this is SORTED! UNIQUE! array
            // 
            // if from left to right is continuous: 
            // right value == left+n 
            // if right cannot be smaller than left+n because we removed duplicated elements
            // if right value is bigger: there are gaps we miss
            // 
            while (right < nUniq && nums[right] < nums[left] + n) right++;

            --right;//  nums[right] == nums[left] + n
            // here the right will be exactly the place we have right value = left + n
            // so from left to right, everything 
            const auto maxContinuousLen = right - left + 1;
            const auto minChangeFromLeft = n - maxContinuousLen;

            minOperations = min(minOperations, minChangeFromLeft);
        }

        return minOperations;        
    }
};
