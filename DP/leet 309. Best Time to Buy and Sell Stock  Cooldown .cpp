/*
Best Time to Buy and Sell Stock with Cooldown

You are given an integer array prices where prices[i] is the price of NeetCoin on the ith day.

You may buy and sell one NeetCoin multiple times with the following restrictions:

After you sell your NeetCoin, you cannot buy another one on the next day (i.e., there is a cooldown period of one day).
You may only own at most one NeetCoin at a time.
You may complete as many transactions as you like.

Return the maximum profit you can achieve.

Example 1:

Input: prices = [1,3,4,0,4]

Output: 6
Explanation: Buy on day 0 (price = 1) and sell on day 1 (price = 3), profit = 3-1 = 2. Then buy on day 3 (price = 0) and sell on day 4 (price = 4), profit = 4-0 = 4. Total profit is 2 + 4 = 6.

Example 2:

Input: prices = [1]

Output: 0
Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000
*/



/*
idea:
     i
    [1,3,4,0,4]
     b h h h
           s
         s c
       s c b
           w w
             b          
     w w ...
       b ...

    every day, with the previous day's operation, you have different choice of operation
    take it then to next day
    -->DP
        maxProfit = max(
                    maxProfit(day2, w),  
                    maxProfit(day2, b),
                    )
    

    complexity:
    O(n^2) !!
    冗余信息：在O(n)版本中，我们只关心“当前是否持有股票”（buying 是 true 还是 false）。而在你这个版本中，你记录了具体哪一天买入的（dealDay）。
    improvement: 在 buy 的当天就直接从总利润里减去 Prices[buy]。
*/

class Solution_dp1 {

private:

    int _maxProfit(const vector<int>& prices, int t, int dealDay, vector<vector<int>>& dp){
        if(t==prices.size()) return 0;

        auto& cache = dp[t][dealDay+2];
        if(cache!=-1){
            return cache;
        }

        if(dealDay == -1) {//cooldown
            cache = _maxProfit(prices, t+1, -2, dp);
        }else if(dealDay == -2) {//did nothing can buy
            cache = max(
                _maxProfit(prices, t+1, -2, dp), 
                _maxProfit(prices, t+1, t, dp)
            );
        }else{// bought at dealday
            if(prices[t] > prices[dealDay]){ // no need to sell for a negative profit
                cache = max(
                    _maxProfit(prices, t+1, dealDay, dp),
                    _maxProfit(prices, t+1, -1, dp) + prices[t] - prices[dealDay]
                    );
            }else{
                cache = _maxProfit(prices, t+1, dealDay, dp);
            }
        }
        return cache;
    }

public:
    int maxProfit(vector<int>& prices) {
        /* 
            dealday = -2: did nothing,
            dealday = -1: selled cooldown,
            dealday >= 0 : deal day,
        */
        const auto n = prices.size();
        vector<vector<int>> dp(n, vector<int>(n+2, -1));
        return max(_maxProfit(prices, 0, -2, dp), _maxProfit(prices, 0, 0, dp));
        
    }
};

// improved: don't use dealDay! let the price alreay passed in the return value, so ere is just a ifelse: status: can I buy?

class Solution_top_down {

private:
    
    int _maxProfit(const vector<int>& prices, int t, bool holdCoin, vector<vector<int>>& dp){
        if(t>=prices.size()) return 0;

        auto& cache = dp[t][holdCoin?1:0];
        if(cache!=-1){
            //return cache;
        }

        if(!holdCoin) {//didn't hold coin
            cache = max(
                _maxProfit(prices, t+1, true, dp) - prices[t], 
                _maxProfit(prices, t+1, false, dp)// wait to buy
            );
        }else{// hold a coin
            cache = max(
                _maxProfit(prices, t+1, true, dp),// hold
                _maxProfit(prices, t+2, false, dp) + prices[t] // cooldown +1 day , 2 days later, I can buy again
            );
      
        }
        return cache;
    }

public:
    int maxProfit(vector<int>& prices) {
        const auto n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return _maxProfit(prices, 0, false, dp);
    }
};
/*

Bottom-up
-1 | 0 | 1             | 2
 B  -p   N[n-1]-p        N[n-1]-p
 S  MIN  B/H[n-1]+p,        
 H   0   B/H[n-1]
 W   0   S/N[n-1]

-1 | 0 | 1             
 B  -3   -3        
 S  MIN  0        
 H   0   0
 W   0   0

 */
class Solution{

public:
    int maxProfit(vector<int>& prices) {
        const auto n = prices.size();
        vector<int> buy(n);
        vector<int> sell(n);
        vector<int> hold(n);
        vector<int> wait(n);

        buy[0] = -prices[0];
        sell[0] = INT_MIN; // no possible on day 0
        hold[0] = INT_MIN; // no possible on day 0
        wait[0] = 0;
        for(int i=1; i<n; ++i){
            buy[i] = wait[i-1] - prices[i];
            sell[i] = max(buy[i-1], hold[i-1])+prices[i];
            hold[i] = max(buy[i-1], hold[i-1]);
            wait[i] = max(sell[i-1], wait[i-1]);
        }

        return max(sell[n-1], wait[n-1]);
    }

};


