/*
Coin Change

You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.

Return the fewest number of coins that you need to make up the exact target amount. If it is impossible to make up the amount, return -1.

You may assume that you have an unlimited number of each coin.

Example 1:

Input: coins = [1,5,10], amount = 12

Output: 3
Explanation: 12 = 10 + 1 + 1. Note that we do not have to use every kind coin available.

Example 2:

Input: coins = [2], amount = 3

Output: -1
Explanation: The amount of 3 cannot be made up with coins of 2.

Example 3:

Input: coins = [1], amount = 0

Output: 0
Explanation: Choosing 0 coins is a valid way to make up 0.

Constraints:

1 <= coins.length <= 10
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10000
*/

/*
idea:  
    greedy: start large ones, if too large to smaller one 
    -> but this may not have the solution: 
        3, 4, 10 -> 16 (10+3+3)

    so we need different branches. 
    DP solution: 
        coinChnage([3,4,10], 16) = min( 
        
          1+coinChnage([], 13)?=-1,
          1+coinChnage([], 12)?=-1,
          1+coinChnage([], 6)?=-1,
        )
    time: O(2^n)

    improvement: cache
    time O(n^2)

*/

class Solution {
private: 
    unordered_map<int, int> memory;
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;

        auto& cache = memory[amount];
        if(cache!=0) return cache; 

        int min_coin = INT_MAX;
        for(auto coin : coins){
            if(coin > amount) continue;
            auto next = coinChange(coins, amount-coin);
            if(next!=-1) min_coin = min(min_coin, next+1);
        }
        return cache  = (min_coin == INT_MAX ? -1 : min_coin);
    }
};



    
class Solution_greedy{
public:
    int coinChange_greedy(const vector<int> & coins, int amount)
    {
        int count = 0;
        for(int i = coins.size()-1; i>=0; --i)
        {
            
            const int currentValue = coins[i];
            const int currentCount = amount/currentValue;
            const int realSum = currentCount*currentValue;
            
            //cout<<"amount : "<<amount<<" currentValue:"<<currentValue<< " realSum:"<<realSum<<endl;
            
            count += currentCount;  
            if(realSum == amount) return count;
            else if(realSum < amount) amount-=realSum;
        }
        return -1;
    }
};
