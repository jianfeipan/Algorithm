/*
Reverse Integer

You are given a signed 32-bit integer x.

Return x after reversing each of its digits. After reversing, if x goes outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0 instead.

Solve the problem without using integers that are outside the signed 32-bit integer range.

Example 1:

Input: x = 1234

Output: 4321
Example 2:

Input: x = -1234

Output: -4321
Example 3:

Input: x = 1234236467

Output: 0
Constraints:

-2^31 <= x <= 2^31 - 1
*/

class Solution {
public:
    int reverse(int x) {
        if(x==INT_MIN) return 0;
        int p = abs(x);
        int reversed = 0;
        while(p){
            if(reversed > INT_MAX/10) return 0;
            reversed*=10;
            reversed += p%10;
            p/=10;
            
        }

        return x>0 ? reversed : -1*reversed;
    }
};
