/*
You are given an array of integers nums and an integer target.

For each number in the array, you can choose to either add or subtract it to a total sum.

For example, if nums = [1, 2], one possible sum would be "+1-2=-1".
If nums=[1,1], there are two different ways to sum the input numbers to get a sum of 0: "+1-1" and "-1+1".

Return the number of different ways that you can build the expression such that the total sum equals target.

Example 1:

Input: nums = [2,2,2], target = 2

Output: 3
Explanation: There are 3 different ways to sum the input numbers to get a sum of 2.
+2 +2 -2 = 2
+2 -2 +2 = 2
-2 +2 +2 = 2

Constraints:

1 <= nums.length <= 20
0 <= nums[i] <= 1000
-1000 <= target <= 1000

*/


/*
idea:
    recursive call:
    dfs( from, nums, target)
    -> current number = nums[from]
    return dfs(from+1, nums, target + current) 
            + dfs(from+1, nums, target - current)
*/
class Solution {
private:
    unordered_map<int, int> memory;
    int dfs(int cur, const vector<int>& nums, int target){
        if(cur == nums.size() && target == 0) return 1;
        if(cur == nums.size()) return 0;

        //1 <= nums.length <= 20
        auto key = target*100 + cur;
        auto it = memory.find(key);
        if(it!=memory.end()) return it->second;

        return memory[key]= 
               dfs(cur +1, nums, target + nums[cur]) 
             + dfs(cur +1, nums, target - nums[cur]);
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        memory.clear();
        return dfs(0, nums, target);
    }
};

