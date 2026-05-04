/*Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.


*/
/*Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.


*/
class Solution {
private:
    unordered_map<int, bool> memory;
    bool dfs(int from, vector<int>& nums, int target){
        if(target == 0) return true;
        if(target<0) return false;
        if(from == nums.size()) return false;
        
        //1 <= nums[i] <= 50
        //1 <= nums.length <= 100
        int key = target*100 + from; 
        if(memory.count(key)) return memory[key];

        return memory[key] = (dfs(from+1, nums, target) || dfs(from+1, nums, target-nums[from]));
    }

public:
    bool canPartition(vector<int>& nums) {
        int total = 0; for(auto num : nums) total+=num;
        if( total%2 == 1) return false;

        // looking subset sum to target = total/2
        // dfs: take or skip current
        return dfs(0, nums, total>>1);
    }
};

