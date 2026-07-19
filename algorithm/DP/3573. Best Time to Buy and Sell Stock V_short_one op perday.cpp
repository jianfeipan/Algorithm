/*
3573. Best Time to Buy and Sell Stock V
Medium


You are given an integer array prices where prices[i] is the price of a stock in dollars on the ith day, and an integer k.

You are allowed to make at most k transactions, where each transaction can be either of the following:

Normal transaction: Buy on day i, then sell on a later day j where i < j. You profit prices[j] - prices[i].

Short selling transaction: Sell on day i, then buy back on a later day j where i < j. You profit prices[i] - prices[j].

Note that you must complete each transaction before starting another. Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.

Return the maximum total profit you can earn by making at most k transactions.

 

Example 1:

Input: prices = [1,7,9,8,2], k = 2

Output: 14

Explanation:

We can make $14 of profit through 2 transactions:
A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.
Example 2:

Input: prices = [12,16,19,19,8,1,19,13,9], k = 3

Output: 36

Explanation:

We can make $36 of profit through 3 transactions:
A normal transaction: buy the stock on day 0 for $12 then sell it on day 2 for $19.
A short selling transaction: sell the stock on day 3 for $19 then buy back on day 4 for $8.
A normal transaction: buy the stock on day 5 for $1 then sell it on day 6 for $19.
 

Constraints:

2 <= prices.length <= 103
1 <= prices[i] <= 109
1 <= k <= prices.length / 2
*/

class Solution_top_down {
private:
    long long _maxProfit(const vector<int>& prices, int t, int k, int status){
        if(t==prices.size()){
            if(status==0){
                return 0;
            }else{
                return INT_MIN; // the final state, we sould only consider cash position.
            }
        }
        if(k==0){//no more transaction can do
            return 0;
        }

        if(status == 0){// cash
            long long profit = 0;
            profit = max(profit, _maxProfit(prices, t+1, k, 0)); // hold cash on day0
            if(k>0){// have quote for transaction
                profit = max(profit, _maxProfit(prices, t+1, k, 1) - prices[t]);// long
                profit = max(profit, _maxProfit(prices, t+1, k, 2) + prices[t]);// short
            }

            return profit;
        }else if(status == 1){//long
            return max(
                _maxProfit(prices, t+1, k, 1),// hold long
                _maxProfit(prices, t+1, k-1, 0) + prices[t] // close position
            );
        }else if(status == 2){//short
            return max(
                _maxProfit(prices, t+1, k, 2), //hold short
                _maxProfit(prices, t+1, k-1, 0) - prices[t]
            );
        }else{
            return -1; // shouldn't reach
        }
    }

public:
    long long maximumProfit(vector<int>& prices, int k) {
        /*
        status:
        0 cash
        1 long_stock
        2 short_stock
        */

        long long profit = 0;
        profit = max(profit, _maxProfit(prices, 0, k, 0)); // hold cash on day0
        profit = max(profit, _maxProfit(prices, 0, k, 1) - prices[0]);// long
        profit = max(profit, _maxProfit(prices, 0, k, 2) + prices[0]);// short

        return profit;

    }
};

class Solution{
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // 使用足够的负无穷，防止减法溢出
        // 假设最高利润不超过 1e15
        const long long INF = 1e15;

        // cash[i] 表示完成 i 次交易（买卖或卖买算一次）
        vector<long long> cash(k + 1, 0);
        // hold_long[i] 表示正在进行第 i 次交易的多头持仓
        vector<long long> hold_long(k + 1, -INF);
        // hold_short[i] 表示正在进行第 i 次交易的空头持仓
        vector<long long> hold_short(k + 1, -INF);

        for (int t = 0; t < n; ++t) {
            // Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.
            // 关键：复制前一天的状态，确保今天的操作基于昨天的结果
            auto prev_cash = cash;
            auto prev_long = hold_long;
            auto prev_short = hold_short;

            for (int i = 1; i <= k; ++i) {
                // 今天如果选择平仓，必须基于昨天的持仓状态
                cash[i] = max({prev_cash[i], 
                               prev_long[i] + prices[t], 
                               prev_short[i] - prices[t]});

                // 今天如果选择开仓，必须基于昨天已完成交易的现金
                hold_long[i] = max(prev_long[i], prev_cash[i-1] - prices[t]);
                hold_short[i] = max(prev_short[i], prev_cash[i-1] + prices[t]);
            }
        }

        return cash[k];

    }
};
