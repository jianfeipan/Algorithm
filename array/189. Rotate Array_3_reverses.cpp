/*
189. Rotate Array
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // three time  reverse
        // nums = [1,2,3,4,5,6,7], k = 3
        // we need 5 6 7 1 2 3 4
        /*
        all reverse:   : 7 6 5 4 3 2 1
        reverse first k: 5 6 7 
        reverse k+1,n-1:       1 2 3 4

        O(n)
        */
        const auto& n = nums.size();
        for(int l=0,r=n-1;l<r; ++l,--r) swap(nums[l], nums[r]);
        
        for(int l=0,r=k-1;l<r; ++l,--r) swap(nums[l], nums[r]);

        for(int l=k,r=n-1;l<r; ++l,--r) swap(nums[l], nums[r]);
    }
};
