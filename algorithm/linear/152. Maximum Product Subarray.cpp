
class Solution {
public:
    // [1, 2, 0 , -3, 4, -5  0, -3, -12, ...]
    // ignore 0s, that makes the choice in no zero segements:
    // the max must be catch when accumulate from left to right or right to left

    // two pass:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int res = nums[0];
        
        { 
            int left = 1;
            for (int i = 0; i < n; i++) {
                left = nums[i] * left;
                res = max(res, left);
                if(left == 0) left = 1;// reset accumulated
            }
        }
        {
            int right = 1;
            for (int i = n-1; i >= 0; --i) {
                right = nums[i] * right;
                res = max(res, right);
                if(right == 0) right = 1; // reset accumulated
            }
        }
        return res;
    }


    // one pass:

    int maxProduct_one_pass(vector<int>& nums) {
        int res = nums[0];
        int cur_min = 1;
        int cur_max = 1;

        for (int num : nums) {
            auto prev_min = cur_min;
            auto prev_max = cur_max;

            cur_min = min({ num * prev_min, num*prev_max, num });
            cur_max = max({ num * prev_min, num*prev_max, num });

            res = max(res, cur_max);
        }
        return res;
    }
};

/*Given an integer array nums, find a subarray that has the largest product within the array and return it.

A subarray is a contiguous non-empty sequence of elements within an array.

You can assume the output will fit into a 32-bit integer.

Example 1:

Input: nums = [1,2,-3,4]

Output: 4
Example 2:

Input: nums = [-2,-1]

Output: 2
Constraints:

1 <= nums.length <= 1000
-10 <= nums[i] <= 10*/
