/*
House Robber
Medium
Topics
Company Tags
Hints
You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a straight line, i.e. the ith house is the neighbor of the (i-1)th and (i+1)th house.

You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

Example 1:

Input: nums = [1,1,3,3]

Output: 4
Explanation: nums[0] + nums[2] = 1 + 3 = 4.

Example 2:

Input: nums = [2,9,8,3,6]

Output: 16
Explanation: nums[0] + nums[2] + nums[4] = 2 + 8 + 6 = 16.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

/*
Facts: 
    no adjacent houses
    target: maximum amount
ideas:
    for each house we can do rob or not, then we have two branches go to next
    -> 
     0 1 2 3
    [1,1,3,3]
    when we come to house 3, if the 2 is robed we go to next, 
    if 2 is not robed , we rob 3 or not then go to next 
    a recursive call, rob(current, robed_last, amount)

    the problem: too many branches and duplicated computations on leaves.
    DP: 
    take | 1 | 1  | 3  | 3  |
    yes. | 1 | 0+1| 1+3| 1+3|     
    no.  | 0 | 1. | 1  | 1+3|
*/
class Solution_DP{// bottom-up
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        vector<int> take(n, 0);
        vector<int> skip(n, 0);

        take[0] = nums[0];
        skip[0] = 0;
        for(int i = 1; i<n; ++i){
            take[i] = nums[i] + skip[i-1];
            skip[i] = max(take[i-1], skip[i-1]);
        }
        return max(take[n-1], skip[n-1]);
    } 
};

class Solution_top_down{ //DFS
private:
    vector<int> cache;
    int _rob_from(const vector<int>& nums, 
             int from){
        if(from >= nums.size()) return 0;
        if(cache[from] != -1) return cache[from];
        cache[from] = max(
            _rob_from(nums, from+1), // skip current
            _rob_from(nums, from+2) + nums[from] //rob current
        );
        return cache[from];
    }
public:
    int rob(vector<int>& nums) {
        cache.resize(nums.size(), -1);
        return _rob_from(nums, 0);
    }
};
