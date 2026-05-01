class Solution {
private:
    void subsets(vector<int>& nums, 
                int from, 
                vector<int>& current, 
                vector<vector<int>>& res){
        if(from == nums.size())  { res.push_back(current); return; }

        // take from
        auto num = nums[from];
        current.push_back(num);
        subsets(nums, from+1, current, res);
        current.pop_back();

        // don't take from
        subsets(nums, from+1, current, res);
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> current;
        subsets(nums, 0, current, res);
        return res;
    }
};

