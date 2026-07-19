class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }

    /*
    Counting subarrays with exactly k distinct values is tricky 
    because adding an element can either increase or maintain the count of distinct 
    values. 
    
    A clever observation is that we can reframe the problem: 
    
    subarrays with exactly k distinct = 
        subarrays with at most k distinct 
        - subarrays with at most k-1 distinct. 
    
    Counting "at most k" is easier using a sliding window 
    that shrinks while we exceed k distinct values.
    */

private:
    int atMostK(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        int res = 0;
        
        int l = 0;
        int r = 0;
        while (r < nums.size()) {
            ++count[nums[r]];
            // when I have >k , ++l to reduce the window
            while (count.size() > k) { 
                --count[nums[l]];
                if (count[nums[l]] == 0) count.erase(nums[l]);
                l++;
            }
            // for every r where we have k distinct, 
            // l     r
            // 0 1 2 3
            // we have r - l +1 : subarrays has <= k distinct
            res += (r - l +1);
            ++r;
        }

        return res;
    }
};
