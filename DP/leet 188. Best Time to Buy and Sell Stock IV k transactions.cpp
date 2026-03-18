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
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        const auto n = prices.size();
        if(n<2) return 0;

        vector<int> cost(n, INT_MAX);
        vector<int> profit(n, INT_MIN);
        for(int i=0; i<n; ++i){
            cost[0] = min(cost[0], prices[i]);
            profit[0] = max(profit[0], prices[i] - cost[0]);

            for(int j = 1; j<k; ++j){
                cost[j]= min(cost[j], prices[i] - profit[j-1]); // j const depends on j-1 profit!!!!
                profit[j]=max(profit[j], prices[i]-cost[j]);
            }
        }
        return profit[k-1];
    }
};
    
