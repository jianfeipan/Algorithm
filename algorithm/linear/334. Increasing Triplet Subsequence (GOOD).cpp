/*
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

 

Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

*/

class Solution {
/*
fact: 
    index should be incremental too
    only yes/no 
idea:
    DP : different cases from first, then second one recursive call

solution:

    you just need 2 compare, find a element, who has two previous elemnt smaller than this one

*/
private:
    
    bool dp(const vector<int>& nums, int currentIndex, int count, vector<vector<int>> & cache)
    {
        if(count == 0) return true;//need three, Compare only twice

        if(cache[currentIndex][count] != -1) return cache[currentIndex][count] == 0 ? false : true;

        for(int i = currentIndex+1; i< nums.size(); ++i) 
        {
            if(nums[currentIndex] < nums[i])
            {
                if(dp(nums, i, count-1, cache)) 
                {
                    cache[currentIndex][count] = 1;
                    return true;
                }
            }
        }
        cache[currentIndex][count] = 0;
        return false;
    }

public:
    bool increasingTriplet_qp(vector<int>& nums) {
        
        vector<vector<int>> cache(nums.size(), vector<int>(3, -1));
        for(int i = 0; i<nums.size(); ++i)
            if(dp(nums, i, 2, cache)) return true;
        return false;
    }


    bool increasingTriplet(vector<int>& nums) {
        int a=INT_MAX,b=INT_MAX;
        for(auto x: nums){
            if(x<=a)    a=x; //there is  x, x> a and x > b, and b > a (only b>a can let enter the second if) 
            else if(x<=b)   b=x;
            else        return true;   
        }
        return false;
    }
};
