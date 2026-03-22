/*829. Consecutive Numbers Sum*/


/*
Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.

 

Example 1:

Input: n = 5
Output: 2
Explanation: 5 = 2 + 3
Example 2:

Input: n = 9
Output: 3
Explanation: 9 = 4 + 5 = 2 + 3 + 4
Example 3:

Input: n = 15
Output: 4
Explanation: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 

*/

class Solution {
/*
n = (first+last)*(last-first+1)/2
n = (2s+l-1)*l/2 = s*l + l*(l-1)/2

s>=1; s<=n
l>=1; s=1 l's max = l+l*(l-1)/2=n

*/
public:
    int consecutiveNumbersSum(int n) {
        int count = 1;
        for(int l=2; l+l*(l-1)/2<=n; ++l){
            // s has solution as int
            if((n - l*(l-1)/2)%l == 0) ++count;
        }
        return count;
    }
};
