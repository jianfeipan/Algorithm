
class Solution {
private:
    void combination_sum(const vector<int>& nums, 
                        int target, 
                        int from, // avoid duplication, 2, 3,4, makes sure noe 2 3 and 3 2
                        vector<int>& current,
                        vector<vector<int>>& res){
        if(0 == target) {res.push_back(current); return;}
        if(from == nums.size()) return;

        auto num = nums[from];
        if(num>target) return;
        
        // take current one
        current.push_back(num);
        combination_sum(nums, target - num, from, current, res);
        current.pop_back(); // backtrace

        // don't take current one
        auto next = from+1;
        // skip duplications
        while(nums[next] == num) ++next;
        combination_sum(nums, target, next, current, res);
    }

public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> current;
        combination_sum(nums, target, 0, current, res);
        return res;
    }
};
/*
You are given an array of integers candidates, which may contain duplicates, and a target integer target. Your task is to return a list of all unique combinations of candidates where the chosen numbers sum to target.

Each element from candidates may be chosen at most once within a combination. The solution set must not contain duplicate combinations.

You may return the combinations in any order and the order of the numbers in each combination can be in any order.

Example 1:

Input: candidates = [9,2,2,4,6,1,5], target = 8

Output: [
  [1,2,5],
  [2,2,4],
  [2,6]
]
Example 2:

Input: candidates = [1,2,3,4,5], target = 7

Output: [
  [1,2,4],
  [2,5],
  [3,4]
]
Constraints:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30

*/


/*
difference: 
    1 not unique, 
    2 only use once
    3 don't output duplicated 

still back track -> i guess this will have duplication problem? YES
how to avoid duplication?
!!! when backtrack: push it, use it, recursive, pop it
this order cannot be changed

to avoid duplication, just when we do "not use it, we shoudld skip all the duplicated" -> wich requires a sort.
*/