class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = -1;
        int right = nums.size();
        int current = 0;
        while(current < right)
        {
            if(nums[current] == 0)
            {
                swap(nums, left+1, current);
                ++left;++current;
            }
            else if(nums[current] == 2)
            {
                swap(nums, right-1, current);
                --right;
            }
            else
                ++current;
        }
    }
    
    void swap(vector<int>& nums, int left, int right)
    {
        int temp =  nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
    }
};
