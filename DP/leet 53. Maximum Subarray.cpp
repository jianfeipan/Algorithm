class Solution_bottom_up_DP {
    
    /*
    Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
    */
public:
    int maxSubArray(vector<int>& nums) {//cumulated sum 
        int maxtail = nums[0];
        int max = nums[0];
        
        for(int i = 1; i<nums.size(); ++i)
        {
            maxtail = std::max(maxtail+nums[i], nums[i]);//take i-1 max sum or not
            max = std::max(max, maxtail);
        }
        
        return max;
    }
};

/*
Given an array of integers nums, find the subarray with the largest sum and return the sum.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [2,-3,4,-2,2,1,-1,4]

Output: 8
Explanation: The subarray [4,-2,2,1,-1,4] has the largest sum 8.

Example 2:

Input: nums = [-1]

Output: -1


*/

/*
idea:
    sum of range: [l, r]
    rightSum
    so any range sum = leftSum[l] - leftsum[r+1]

    we need to find  l and r makes the max 
*/

class Solution_leftSum {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> leftSum(nums.size()+1);
        for(int i=0; i<nums.size(); ++i){
            leftSum[i+1]+=leftSum[i]+nums[i];
        }

        int maxSum = INT_MIN;
        for(int l=0; l<nums.size(); ++l){
            for(int r=l; r<nums.size(); ++r){
                auto sum = leftSum[r+1] - leftSum[l];
                maxSum = max(maxSum, sum);
            }
        }
        return maxSum;
    }
};

class Solution { // DP
private:
    int maxFrom(const vector<int>& nums,
                int from, vector<int>& memory){ // max subarray sum to left
        if(from == nums.size()) return 0;

        auto& cache = memory[from];
        if(cache!=-1) return cache;

        int nextMax = maxFrom(nums, from+1, memory);
        return cache = (nextMax>0 ? nums[from]+nextMax : nums[from]);
    }
public:
    int maxSubArray__(vector<int>& nums) {
        int maxSum = INT_MIN;
        vector<int> memory(nums.size(), -1);
        for(int i = 0; i<nums.size(); ++i){
            maxSum = max(maxSum, 
                        maxFrom(nums, i, memory));
        }
        return maxSum;
    }
    
};
