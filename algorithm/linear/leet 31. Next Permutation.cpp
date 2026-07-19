class Solution {
public:
    void nextPermutation(vector<int>& nums)
    {
        /*
        find the last rising pair
        */
        
        if(nums.size() <= 1) return;
        
        int i = nums.size()-2;
        while(i>=0 && nums[i] >= nums[i+1]) --i;
        
        if(i == -1) 
            reverse(nums.begin(), nums.end());
        else
        {
            int j = i+1;
            while(j<nums.size() && nums[i]<nums[j]) ++j;//smallest in right bigger than nums i
            
            swap(nums, i, j -1);
            
            reverse(nums.begin() + i +1, nums.end());
        }
        
    }
    
    
    void swap(vector<int> & nums, int left, int right)
    {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
     }
};
