/*
There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:

In each step, you will choose any 3 piles of coins (not necessarily consecutive).
Of your choice, Alice will pick the pile with the maximum number of coins.
You will pick the next pile with the maximum number of coins.
Your friend Bob will pick the last pile.
Repeat until there are no more piles of coins.
Given an array of integers piles where piles[i] is the number of coins in the ith pile.

Return the maximum number of coins that you can have.

 

Example 1:

Input: piles = [2,4,1,2,7,8]
Output: 9
Explanation: Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile with 2 coins and Bob the last one.
The maximum number of coins which you can have are: 7 + 2 = 9.
On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6 coins which is not optimal.
Example 2:

Input: piles = [2,4,5]
Output: 4
Example 3:

Input: piles = [9,8,7,6,5,1,2,3,4]
Output: 18

*/

class Solution {

/*
fact:
    1. chose 3,then get the middle
    2. greedy maybe not the best
    3. for the 3 piles (S<M<L), we need to make the S as small as we can and L-M as small as we can 
idea:
    1 sort will be a good start [8,7,4,2,2,1]
    2 From the biggest, we can only get [7,2] -> 9 



*/
public:
    int maxCoins(vector<int>& piles) {
        std::sort(piles.begin(), piles.end(), std::greater<int>());
        int res = 0;
        for(int i = 0; i<piles.size()/3; ++i)
        {
            res+=piles[2*i +1];
        }
        return res;
    }
};
