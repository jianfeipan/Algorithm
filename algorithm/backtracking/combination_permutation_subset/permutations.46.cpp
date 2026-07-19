/*
swap thinking: 
every element to be in any position: 
the element at start, to be in any other places [start, n-1]
every possible value, we combine it with swaps on start+1. (this value to be on start, is already covered by start sawp). 
backtrace, to next 

O(N*N!) permutation N! each one we copy the vector O(N)
*/

class Solution {
private:
    void permute_from(int from, vector<int>& nums, vector<vector<int>>& res) {
        if (from == nums.size()) {
            res.push_back(nums); // fully swapped produce one result
            return;
        }

        for (int i = from; i < nums.size(); ++i) {// all possibilities on from
            swap(nums[from], nums[i]);// also do for from, which means no swap, take the current result.
            permute_from(from + 1, nums, res);
            swap(nums[from], nums[i]); // backtrack
        }
    }   
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // swap: [1, ... i, [i+1, i+2 ... n-1 ]] swap i with all [i+1, n-1]
        vector<vector<int>> res;
        permute_from(0, nums, res);
        return res;
    }
};

class Solution_permutation_with_duplication {
private:
    void permutations_(int from, vector<int>& current, vector<vector<int>>& res){
        if(from == current.size()) { res.push_back(current); return; }

        unordered_set<int> visited;
        for(int i = from; i<current.size(); ++i){
            if(visited.count(current[i])) continue;

            visited.insert(current[i]);
            swap(current[from], current[i]);
            permutations_(from+1, current, res);
            swap(current[from], current[i]);
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        permutations_(0, nums, res);
        return res;
    }
};
