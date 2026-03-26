/*
You are given an integer array nums where each element nums[i] indicates your maximum jump length at that position.

Return true if you can reach the last index starting from index 0, or false otherwise.

Example 1:

Input: nums = [1,2,0,1,0]

Output: true
Explanation: First jump from index 0 to 1, then from index 1 to 3, and lastly from index 3 to 4.

Example 2:

Input: nums = [1,2,1,0,1]

Output: false


idea:
    recursive: canJumpFrom(index, nums, ){
                    if(nums[index] == 0 ) return false; // trap
                    return canJumpFrom(index+nums[index], nums)
                }
*/

class Solution {
private:
    bool canJump(int from, const vector<int>& nums){
        if(from == nums.size()-1) return true;
        if(nums[from] == 0) return false;
        for(int step = 1; step<= nums[from]; ++step){
            if(canJump(step+from, nums)){
                return true;
            }
        }
        return false;
    }
public:
    bool canJump(vector<int>& nums) {
        if(nums.empty()) return false;//invalid input
        return canJump(0, nums);
    }
};
