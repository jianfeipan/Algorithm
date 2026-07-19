class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> exist(nums.begin(), nums.end());
        int longest = 1;
        for(const auto& num : nums){
            if(num == 0 || !exist.count(num-1)){
                // num could be a start
                int next = num+1;
                while(exist.count(next)){
                    ++next;
                }
                longest = max(longest, next - num);
            }
            //!!!!!!!, this is important else num is not a start, it has one number before it just skip
        }
        return longest;
    }
};
