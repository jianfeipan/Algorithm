/*
nums = [1,2,3]


permute                      [1] 
permute             [1,2],               [2,1] -> add 2 to all possible positions of permut [1] 
permut2 [1,2,3]  [312]  [132]      [321] [231] [213] -> add 3 to all possible positions of permute [1,2]
*/
class Solution_insertion { // inserting thinking O(N*N!)
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

O(N*N!) permutation N! each one we copy the vector O(N)
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
