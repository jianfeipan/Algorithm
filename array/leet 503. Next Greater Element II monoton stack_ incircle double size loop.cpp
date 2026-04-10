class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> nextGreater(nums.size(), -1);
        stack<int> decreasing;
        for(int j=0; j<2*nums.size(); ++j){
            int i = j%nums.size();
            while(!decreasing.empty() && nums[decreasing.top()] < nums[i]){
                nextGreater[decreasing.top()] = nums[i];
                decreasing.pop();
            }
            decreasing.push(i);
        }

        return nextGreater;
    }
};
