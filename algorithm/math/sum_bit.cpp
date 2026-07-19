/*

Given two integers a and b, return the sum of the two integers without using the + and - operators.

Example 1:

Input: a = 1, b = 1

Output: 2
Example 2:

Input: a = 4, b = 7

Output: 11
Constraints:

-1000 <= a, b <= 1000
*/
#include <format>
class Solution {
public:
    int getSum(int a, int b) {
        int res=0;
        int carry=0;
        for (int i = 0; i < 32; i++) {
            // Extract the i-th bit of a and b
            int bitA = (a >> i) & 1;
            int bitB = (b >> i) & 1;

            int currentBit = bitA ^ bitB ^ carry;//XOR
            carry = (bitA & bitB) | (carry & (bitA ^ bitB));
            // Write the sumBit into the result at the correct position
            res |= (currentBit << i);
        }
        return res;
    }
};
