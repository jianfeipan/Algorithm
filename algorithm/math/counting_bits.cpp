/*
Given an integer n, count the number of 1's in the binary representation of every number in the range [0, n].

Return an array output where output[i] is the number of 1's in the binary representation of i.

Example 1:

Input: n = 4

Output: [0,1,1,2,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100

*/

class Solution {

public:
    vector<int> countBits(int n) {
        vector<int> bits(n+1);
        for(int i = 1; i<=n ; ++i) {
            // 1011 is from 101<<1 and plus i&1 = 1
            // 1010 is from 101<<1 and plus i&1 = 0 
            bits[i] = bits[i>>1] + (i&1);
        }
        return bits;
    }
};
