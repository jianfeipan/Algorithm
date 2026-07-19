class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 1;
        int candidate = nums.front();

        for (int i = 1; i<nums.size(); ++i) 
        {
            
            if (count == 0) 
            {
                candidate = nums[i];
                ++count;
            }
            else
            {
                count += (nums[i] == candidate) ? 1 : -1;
            }
        }

        return candidate;
    }
};
