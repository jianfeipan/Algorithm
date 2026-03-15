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
    int _rob_no_circle(const vector<int>& nums, int from, int to){
        // if no circle
        if(from == to) return nums[from];
        const auto& n = nums.size();
        vector<int> take(n, 0); // max if take current i
        vector<int> skip(n, 0); // max if skip current i

        take[from] = nums[from];

        for(int i=1; i<=to; ++i){
            // if take current i-1 must skip
            take[i] = skip[i-1]+nums[i];
            // if skip current, i-1 could be skipped or taken
            skip[i] = max(skip[i-1], take[i-1]);
        }

        return max(take[to], skip[to]);
    }
public:
    int rob(vector<int>& nums) {
        const auto& n = nums.size();
        if(n==1) return nums[0];

        // with circle, 0 and n-1 cannot be robed at the same time:
        // skip 0: 
        const auto skipFirstMax = _rob_no_circle(nums, 1, n-1);

        // skip: n-1
        const auto skipLastMax = _rob_no_circle(nums, 0, n-2);

        return max(skipFirstMax, skipLastMax);

    }
};
