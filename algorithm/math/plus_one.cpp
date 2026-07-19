/*

Plus One
Solved 
Easy
Topics
Company Tags
Hints
You are given an integer array digits, where each digits[i] is the ith digit of a large integer. It is ordered from most significant to least significant digit, and it will not contain any leading zero.

Return the digits of the given integer after incrementing it by one.

Example 1:

Input: digits = [1,2,3,4]

Output: [1,2,3,5]
Explanation 1234 + 1 = 1235.

Example 2:

Input: digits = [9,9,9]

Output: [1,0,0,0]
Constraints:

1 <= digits.length <= 100
0 <= digits[i] <= 9
*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res = digits;
        int carry = 1;
        for(int i=res.size()-1; i>=0; --i){
            int current = digits[i]+carry;
            if(current<10){
                carry = 0;
                res[i] = current;
                break;
            }else{
                res[i] = current%10;
            }
        }
        if(carry == 1){
            res.insert(res.begin(), 1);
        }
        return res;
    }
};
