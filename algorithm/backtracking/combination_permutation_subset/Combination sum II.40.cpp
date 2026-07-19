class Solution {
private:
    void combination_sum(const vector<int>& nums, 
                        int target, 
                        int from, 
                        vector<int>& current,
                        vector<vector<int>>& res){
        if(0 == target) {res.push_back(current); return;}
        if(from == nums.size()) return;

        auto num = nums[from];
        if(num>target) return;
        
        // take current one
        current.push_back(num);
        combination_sum(nums, target - num, from+1, current, res);
        current.pop_back(); // backtrace

        // don't take current one: basically it means don't take any current `num`
        // we need to skip all equals, prerequest is sort
        auto next = from+1;
        // skip duplications
        while(next<nums.size() && nums[next] == num) ++next;
        combination_sum(nums, target, next, current, res);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> current;
        combination_sum(candidates, target, 0, current, res);
        return res;
    }
};

