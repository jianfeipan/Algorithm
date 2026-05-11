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

class Solution_with_duplications {

private:
    void subset_(const vector<int>& nums, int from, vector<int>& current, vector<vector<int>>&res){
        res.push_back(current); // Every node in the tree is a valid subset

        for (int i = from; i < nums.size(); ++i) {
            // CRITICAL: Skip duplicates. 
            // If this is not the first time we are picking an element for this 'slot'
            // and it's the same as the previous element, skip it.
            if (i > from && nums[i] == nums[i-1]) continue;

            current.push_back(nums[i]);
            subset_(nums, i + 1, current, res);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        vector<int> current; current.reserve(nums.size());
        subset_(nums, 0, current, res);
        return res;
    }
};

