class Solution {

/*
Description
Given an array contains N numbers of 0 .. N, find which number doesn't exist in the array.

Example
Example 1:

Input:[0,1,3]
Output:2
Example 2:

Input:[1,2,3]
Output:0
Challenge
Do it in-place with O(1) extra memory and O(n) time.
*/
public:
    /**
     * @param nums: An array of integers
     * @return: An integer
     */
    int findMissing(vector<int> &nums) {
        //idea use theorical sum - real sum will find the missing number

        int sum = ((1+nums.size()) * nums.size()) >> 1;
        for(int n : nums)
        {
            sum-=n;
        }
        return sum;
    }
};
