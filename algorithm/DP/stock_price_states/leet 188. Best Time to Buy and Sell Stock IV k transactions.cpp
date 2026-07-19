/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/

// min cost , max profit , buy then share, so you have cost first, then profit = price - cost, then next cost will be profit[i-1] - price
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<int> cost(k, 10000000);
        vector<int> profit(k, -1000000);

        for(auto price : prices){
            for(int i=0; i<k; ++i){
                cost[i] = min(cost[i], i == 0? price : price - profit[i-1]); // !!! 1 th cost depends on i-1 profit
                profit[i] = max(profit[i], price - cost[i]);
            }
        }
        return profit[k-1];
    }
};
    
