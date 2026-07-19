class Solution {
    /*
    Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.

 

Example 1:

Input: left = 5, right = 7
Output: 4


00001
00010
00011<left
00100
00101
00110<right
00111
.....
    
    only the heighest comment bit rest!!!
    
    
    */
    
public:
    int rangeBitwiseAnd(int left, int right) {
        if(left == 0) return 0;

        int moveFactor = 1;
        while(left != right)
        {
            left >>= 1;
            right >>= 1;
            moveFactor <<= 1;
        }
        return left * moveFactor;
        
    }
};
