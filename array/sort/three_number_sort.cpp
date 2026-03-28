/*
sort colors
You are given an array nums consisting of n elements where each element is an integer representing a color:

0 represents red
1 represents white
2 represents blue
Your task is to sort the array in-place such that elements of the same color are grouped together and arranged in the order: red (0), white (1), and then blue (2).

You must not use any built-in sorting functions to solve this problem.

Example 1:

Input: nums = [1,0,1,2]

Output: [0,1,1,2]
Example 2:

Input: nums = [2,1,0]

Output: [0,1,2]
Constraints:
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l=0; 
        int r = nums.size()-1;
        int i=0;
        while(i<=r){
            if(nums[i] == 0){
                swap(nums[l], nums[i]);
                ++l;
            }else if(nums[i]==2){
                swap(nums[r], nums[i]);
                --r;
            }
            ++i;
        }
    }
};
