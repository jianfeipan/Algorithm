
/*
You are given a 0-indexed integer array nums. In one operation, select any non-negative integer x and an index i, then update nums[i] to be equal to nums[i] AND (nums[i] XOR x).

Note that AND is the bitwise AND operation and XOR is the bitwise XOR operation.

Return the maximum possible bitwise XOR of all elements of nums after applying the operation any number of times.

 

Example 1:

Input: nums = [3,2,4,6]
Output: 7
Explanation: Apply the operation with x = 4 and i = 3, num[3] = 6 AND (6 XOR 4) = 6 AND 2 = 2.
Now, nums = [3, 2, 4, 2] and the bitwise XOR of all the elements = 3 XOR 2 XOR 4 XOR 2 = 7.
It can be shown that 7 is the maximum possible bitwise XOR.
Note that other operations may be used to achieve a bitwise XOR of 7.
Example 2:

Input: nums = [1,2,3,9,2]
Output: 11
Explanation: Apply the operation zero times.
The bitwise XOR of all the elements = 1 XOR 2 XOR 3 XOR 9 XOR 2 = 11.
It can be shown that 11 is the maximum possible bitwise XOR.

*/
class Solution {

/*
Fact:
    1. theoretical max is 1111..1 with the max lenght of num
    2. "any number of times" mean cannot do brute force
    3. there must be some pattern when we apply "nums[i] = nums[i] AND (nums[i] XOR x)"
        -> 
            x 0 0 1 1
            y 0 1 0 1
            ---------------------
          x^y 0 1 1 0
            -------------------
      x&(x^y) 0 0 1 0  
        --> what it's doing is transform x = 1 to x = 0 when y = 1. 
    4. if we focus on one bit, in the nums of the vector, we will have m 0s and n 1s
        --> we don't care 0s, all 0 will XOR to one 0
        --> we care even 1 or odd 1, even --> XOR = 0 and odd 1 will XOR to 1 


Idea:
   combine 3, and 4 : if we have one 1 on this bit, we could make it to 1 in the end: single 1 is already 1, double 1 can apply 3 for change to odd 1
   --> if all zero, it will stay 0

*/

public:
    int maximumXOR(vector<int>& nums) {
        int res = 0;
        for(int num : nums)
        {
            res|=num;
        }

        return res;
    }
};
