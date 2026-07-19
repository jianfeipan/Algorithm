/*
You are given an array of integers nums, where nums[i] represents the maximum length of a jump towards the right from index i. For example, if you are at nums[i], you can jump to any index i + j where:

j <= nums[i]
i + j < nums.length
You are initially positioned at nums[0].

Return the minimum number of jumps to reach the last position in the array (index nums.length - 1). You may assume there is always a valid answer.

Example 1:

Input: nums = [2,4,1,1,1,1]

Output: 2
Explanation: Jump from index 0 to index 1, then jump from index 1 to the last index.

Example 2:

Input: nums = [2,1,2,1,0]

Output: 2
*/

/*
idea:
    recursive jumpFrom index
    loop all next points and call jumpFrom 
    leaves will be computed many times -> memory 
    top-down DP 
*/
class Solution {
private:
    int minJump(int from, const vector<int>& nums, vector<int>& memory){
        if(from >= nums.size()) return INT_MAX;
        if(from == nums.size() - 1) return 0;

        auto& cache = memory[from];
        if(cache != -1) return cache;
        
        int minJumpCount = INT_MAX;
        for(int step = 1; step<=nums[from] && step+from < nums.size(); ++step){
            auto nextJumps = minJump(step+from, nums, memory);
            if(nextJumps!=INT_MAX) {
                minJumpCount = min(minJumpCount, nextJumps+1);
            }
        }
        return cache = minJumpCount;
    }
public:
    int jump(vector<int>& nums) {
        vector<int> memory(nums.size(), -1);
        return minJump(0, nums, memory);
    }
};
