/*
House Robber II
Medium
Topics
Company Tags
Hints
You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a circle, i.e. the first house and the last house are neighbors.

You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

Example 1:

Input: nums = [3,4,3]

Output: 4
Explanation: You cannot rob nums[0] + nums[2] = 6 because nums[0] and nums[2] are adjacent houses. The maximum you can rob is nums[1] = 4.

Example 2:

Input: nums = [2,9,8,3,6]

Output: 15
Explanation: You cannot rob nums[0] + nums[2] + nums[4] = 16 because nums[0] and nums[4] are adjacent houses. The maximum you can rob is nums[1] + nums[4] = 15.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 200*/


/*
So we already have the DP solution for no circle, which mean n-1 and 0 are independent
[0 1 2 3 4]

        | 3 | 4   | 3     |
    take| 3 | 0+4 | 3+0+3 |
    skip| 0 | 3+0 | 0+4+0 |

*/
class Solution {
private:
    vector<int> memory;
    int rob_from(int cur, const vector<int>& nums){
        if(cur >= nums.size()) return 0;

        auto& cache = memory[cur];
        if(cache!=-1) return cache;
        return cache = max(
            rob_from(cur+2, nums) + nums[cur],  // rob current
            rob_from(cur+1, nums) + 0); // skip current
    }
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums.at(0);

        memory = vector<int>(nums.size(), -1);
        auto skip_0 = rob_from(1, nums);

        // if we don't want to skip 0, then the last we don't take:
        memory = vector<int>(nums.size(), -1); // !!! reset memory!!
        nums.back()= 0;//!!! 
        auto rob_0 = rob_from(0, nums);
        return max(rob_0, skip_0);
    }
};

