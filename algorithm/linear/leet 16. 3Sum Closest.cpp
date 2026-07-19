class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) 
    {
        
        sort(nums.begin(), nums.end());
       
        int closest = nums[0] + nums[1] + nums[2];
            
        for(int i = 0; i<nums.size()-2; ++i)
        {
            int left = i+1;
            int right = nums.size() -1;
            
            int targetSum = target - nums[i];
            while(left < right)
            {
                int currentSum = nums[left] + nums[right];
                
                if(currentSum == targetSum) return target;
                
                if(abs(currentSum - targetSum) < abs(closest - target))
                    closest  = currentSum+nums[i];
                
                if(nums[left] + nums[right] < targetSum)
                    ++left;
                else
                    --right;
            }
            

        }
        
        return closest;
    }
};
