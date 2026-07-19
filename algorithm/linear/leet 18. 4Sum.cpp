class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {//O(N^3) where two sum is N with sorted solution
        
        vector<vector<int>> res;
        if(nums.size()<4)
            return res;
        
        sort(nums.begin(), nums.end());

        int prev;
        bool first = true;
        
        for (int firstIndex = 0; firstIndex<= nums.size()-4;  firstIndex++) {
            int num1 = nums[firstIndex];
            if (!first && prev == num1)
                continue;
            else {
                first = false;
                prev = num1;
            }
            
            int prev2;
            bool first2 = true;
            for(int secondIndex = firstIndex+1; secondIndex<= nums.size()-3;  secondIndex++) 
            {
                int num2 = nums[secondIndex];
                if (!first2 && prev2 == num2)
                    continue;
                else {
                    first2 = false;
                    prev2 = num2;
                }
                
                
                int *lo = &nums[secondIndex+1];
                int *hi = &nums.back();
                while (lo < hi) {
                    int sum = *lo + *hi + num1 + num2;
                    if (sum == target) {
                        res.emplace_back(vector<int>{num1, num2, *lo, *hi});
                        while (++lo < hi && *(lo - 1) == *lo);//skip same values
                        while (--hi > lo && *hi == *(hi + 1));//skip same values
                    } else if (sum < target)
                        ++lo;
                    else
                        --hi;
                }
            }
        }
        return res;
    }
};
