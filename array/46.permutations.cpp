/*

Topics
premium lock icon
Companies
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]

*/

/*

nums = [1,2,3]


permute                      [1] 
permute             [1,2],               [2,1] -> add 2 to all possible positions of permut [1] 
permut2 [1,2,3]  [312]  [132]      [321] [231] [213] -> add 3 to all possible positions of permute [1,2]
*/
class Solution_insertion { // inserting thinking
private:

    vector<vector<int>> permute(const vector<int>& nums, int from){
        if(from == nums.size()-1) return {{nums[from]}};

        auto permutes = permute(nums, from+1);
        const auto& curr = nums[from];

        vector<vector<int>> newPermutes;
        for(auto& permute : permutes){
            for(int i=0; i<=permute.size(); ++i){
                vector<int> newPermute = permute;
                newPermute.insert(newPermute.begin()+i, curr);
                newPermutes.emplace_back(move(newPermute));
            }
        }
        
        return newPermutes;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return permute(nums, 0);
    }
};
/*


swap thinking: 
every element to be in any position: 
the element at start, to be in any other places [start, n-1]
every possible value, we combine it with swaps on start+1. (this value to be on start, is already covered by start sawp). 
backtrace, to next 

*/
class Solution{
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);      // Swap to fix one element
            backtrack(nums, start + 1, result);  // Recurse for the rest
            std::swap(nums[start], nums[i]);      // Backtrack (swap back)
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }
};
