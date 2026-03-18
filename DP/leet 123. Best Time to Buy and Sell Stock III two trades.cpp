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
    
Class Solution {
private:
    int DP_bottom_up(const vector<int>& prices) {
        if(prices.empty()) return 0;

        const auto n = prices.size();
        int buy1    = INT_MAX;
        int profit1 = INT_MIN;
        int buy2    = INT_MAX;
        int profit2 = INT_MIN;

        for(int i=1; i<n; ++i){
            buy1    = min(buy1, prices[i]); // minimum the cost
            profit1 = max(profit1, prices[i] - buy1); // maximum the profit

            buy2    = min(buy2, prices[i] - profit1); 
            // if you do the second buy here, the min total cost is the price and the max profit from the first buy=sell 
            profit2 = max(profit2, prices[i] - buy2);
            // if you sell here, the max profit is the current price - the total cost which is the buy2, and the first transaction is embaded in the buy2 info)
        }

        return profit2; // no need to check profit1: it's the same you do first transaction on the same date.
    } 



public:
    int maxProfit(vector<int>& prices) {
        return DP_bottom_up(prices);
    }
};
    

class Solution_from_one_buy_obe_sell{
    int maxProfit_brute_force_leftMax_rightMax(vector<int>& prices) 
    {
        /*
        we know how to get on trasaction maxProfit, so just chose on date, we can compute left max and right max, then we iterate on all dates to find the max
        
        O(N^2)
        */
        
        int maxProf = 0;
        
        for(size_t i = 0; i<prices.size(); ++i)
        {
            const int towTrasaction = maxProfit_one_trasaction(prices, 0, i)  
                + maxProfit_one_trasaction(prices, i+1, prices.size() -1) ;
            maxProf = max(maxProf, towTrasaction);
        }
        
        return maxProf;
            
    }
    
    int maxProfit_one_trasaction(const vector<int>& prices, size_t from, size_t to)
    {
        int maxProf = 0;
        int minPrice = INT_MAX;
        
        for(size_t i = from; i<=to; ++i)
        {
            minPrice = min(minPrice, prices[i]);
            maxProf = max(maxProf, prices[i] - minPrice);
        }
        return maxProf;
    }

};
