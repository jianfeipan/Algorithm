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


/*
idea:
    BF O(n^2)  to find all combinations and note the max
    what's duplicated: multilication of all small grups
    
    The maximum-product subarray problem is tricky because:

idea1: segements!
    A negative number flips the sign (a very small negative can become a very large positive after another negative).
    A zero breaks any product (anything crossing a zero becomes 0).
    So we can treat the array as separate segments split by zeros.
    Inside one zero-free segment:

    If the count of negative numbers is even, the product of the whole segment is positive → usually the best.
    If the count is odd, we must drop either the prefix up to the first negative or the suffix after the last negative to make the remaining product have an even number of negatives.
idea2 two pass! accumulation!
    in a no zero segementation, the max is produced during we loop to left to right or from right to left

*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxProduct = nums[0];

        int leftProduct = 1; //-> this is very smart to manage the 0 values.
        for(int i=0; i<nums.size(); ++i){
            if(leftProduct==0){// when we have zero, we reset the accumulated product to 1
                leftProduct=1;
            }
            leftProduct *= nums[i];
            maxProduct = max(maxProduct, leftProduct);
        }
        int rightProduct = 1;
        for(int i=nums.size()-1; i>=0; --i){
            if(rightProduct==0){
                rightProduct=1;
            }
            rightProduct*=nums[i];
            maxProduct = max(maxProduct, rightProduct);
        }
        
        return maxProduct;
    }
};
