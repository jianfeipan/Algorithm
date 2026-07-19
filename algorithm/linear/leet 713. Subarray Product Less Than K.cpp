class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) 
    {
        return numSubarrayProductLessThanK_sliding_window(nums, k);
    }
    
    int numSubarrayProductLessThanK_sliding_window(vector<int>& nums, int k) 
    {
        if (k == 0) return 0;
        
        int count = 0;
        size_t from = 0;
        size_t to = 0;
        int prod = 1;
        
        while(to<nums.size())
        {
            prod*=nums[to];
            while(from<=to && prod>=k) prod/=nums[from++];
            
            count+=to - from + 1;//cout<<from<<","<<to<<endl;
            
            ++to;
        }
        return count;
        
    }
    
    int numSubarrayProductLessThanK_Brute_force(vector<int>& nums, int k) 
    {
        int count = 0;
        for(size_t from = 0; from<nums.size(); ++from)
        {
            int product = 1;
            for(size_t to = from; to<nums.size(); ++to)
            {
                product*=nums[to];
                if(product<k) ++count;
                else break;
            }
        }
        return count;
    }
    
    

};
