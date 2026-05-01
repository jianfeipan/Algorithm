
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
        combination_sum(nums, target, from+1, current, res);
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
Input:
nums = [2,5,6,9]
target = 9

Output: [[2,2,5],[9]]



fact:
    nums are distinct, to get the target we can use any number multipal times.
idea:
    any number n beyond target, we can ignore them
    any number n we can used or not used. if it's used, can be multipal times 
    let's have a pointer, and recursivly move it to the right

this is called back track!!
*/