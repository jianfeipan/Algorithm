/*
300. Longest Increasing Subsequence
Longest Increasing Subsequence
Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from the given sequence by deleting some or no elements without changing the relative order of the remaining characters.

For example, "cat" is a subsequence of "crabt".
Example 1:

Input: nums = [9,1,4,2,3,3,7]

Output: 4
Explanation: The longest increasing subsequence is [1,2,3,7], which has a length of 4.

Example 2:

Input: nums = [0,3,1,3,2,3]

Output: 4
Constraints:

1 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
*/

class Solution_DP_top_down {
/*
idea: 
    start from i, find next bigger one, 
    take it: recursively to next
    skip it: recursively to next
    note current depth, and max value so far
complexity: 
    how many time we will call recursive: with cache DP: n
    how many operations we do in recursive function: n
    O(n^2)
    
*/
private:
    int _lengthOfLIS(const vector<int>& nums,
                     int from, vector<int>& dp){
        if(dp[from] != -1){
            return dp[from];
        }

        int imaxDepth=1;

        for(int i=from+1; i<nums.size(); ++i){
            if(nums[i] > nums[from]){
                //take it
                imaxDepth = max(imaxDepth, 
                _lengthOfLIS(nums, i, dp) + 1);
            }
        }
        return dp[from] = imaxDepth;
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);

        int maxDepth = 1;
        for(int i=0; i<nums.size(); ++i){
            maxDepth = max(maxDepth, 
            _lengthOfLIS(nums, i, dp));
        }
        return maxDepth;
    }
};

// pure recursion 
class Solution {
private:
    int longest_from(int from, int last_taken, const vector<int>& nums){
        if(from == nums.size()) return 0;
        if(last_taken != -1 && nums[last_taken] >= nums[from]) return 0;
        
        // take current or skip current
        return max(
            1 + longest_from(from+1, from, nums),
            longest_from(from+1, last_taken, nums)
        );
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        return longest_from(0, -1, nums);
    }
};
