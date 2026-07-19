class Solution {
public:
    int triangleNumber(vector<int>& nums) 
    {
        return triangleNumber_binarySearch(nums);
    }

    int triangleNumber_binarySearch(vector<int>& nums) 
    {
        if(nums.size() < 3) return 0;
        
        int count = 0;
        sort(nums.begin(), nums.end());
        for(int pivot = 0; pivot<nums.size()-2; ++pivot)
        {
            for(int left = pivot+1; left<nums.size()-1; ++left)
            {
                auto upperBoundIndex = upperBound(nums[left] + nums[pivot], nums, left+1,nums.size()-1);
                count+=(upperBoundIndex-left-1);
            }
        }
        
        return count;
    }
    
    int triangleNumber_bruteForce(vector<int>& nums) 
    {
        if(nums.size() < 3) return 0;
        
        int count = 0;
        sort(nums.begin(), nums.end());
        for(int pivot = 0; pivot<nums.size()-2; ++pivot)
        {
            for(int left = pivot+1; left<nums.size()-1; ++left)
            {
                for(int right = left+1; right<nums.size();++right)
                {
                    if(nums[pivot] + nums[left] > nums[right]) ++count;//---> a binary search smell 
                }
            }
        }
        
        return count;
    }
    
private:
    int upperBound(int upper, const vector<int>& nums, int from, int to)
    // find first element bigger or equals this upper
    {
        while(from<=to && to<nums.size())
        {
            int mid = (from + to)>>1;

            if(nums[mid] < upper)
                //let th == in left side, so in the end we take from, will be the first elelemtn bigger than upper
                from = mid+1;
            else
                to = mid-1;
        }
        
        return from;
    }
    
    int lowerBound(int lower, const vector<int>& nums, int from, int to)
    //find the first element bigger than this
    {
        while(from<=to && to<nums.size())
        {
            int mid = (from + to)>>1;

            if(nums[mid] <= lower)
                from = mid+1;
            else
                to = mid-1;
        }
        
        return to;
    }
};
