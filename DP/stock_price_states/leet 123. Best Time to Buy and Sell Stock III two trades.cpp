class Solution {
    /*
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

idea : what we should find is two pairs or one pair to have biggest profit, and two pairs cannot have overlapping
    */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold_cash0 = 0;
        int hold_stock1 = -prices[0];
        int hold_cash1 = -100000;
        int hold_stock2 = -100000;
        int hold_cash2 = -100000; // cannot be INT_MIN -> UB when you do INT_MAX - prices

        for(int t=1; t<prices.size(); ++t){
            int prev_cash0 =hold_cash0;
            int prev_stock1=hold_stock1;
            int prev_cash1 =hold_cash1;
            int prev_stock2=hold_stock2;
            int prev_cash2 =hold_cash2;

            hold_cash0 = prev_cash0;
            hold_stock1 = max(prev_stock1, prev_cash0 - prices[t]);
            hold_cash1 = max(prev_cash1, prev_stock1 + prices[t]);
            hold_stock2 = max(prev_stock2, prev_cash1 - prices[t]);
            hold_cash2 = max(prev_cash2, prev_stock2 + prices[t]);
        }

        return max(hold_cash0, max(hold_cash1, hold_cash2));
    }
};