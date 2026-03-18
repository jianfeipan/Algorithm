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
    
public:
    int maxProfit(vector<int>& prices) 
    {
        return maxProfit_DP_with_MaxDiff(prices);
    }
    
private:
    
    int maxProfit_DP_with_MaxDiff(const vector<int>& prices) //O(N)
    {
        /*
        checking the last DP solution, we can find there are things we duplicated : 
        in this part : 
        
        int maxIfSellThisDay = 0;
        for(int buyDay = 1; buyDay < day; ++buyDay)
        {
            const int buyDayProfit = maxProfits[tradeNb-1][buyDay-1] + prices[day-1] - prices[buyDay-1];
            maxIfSellThisDay = max(maxIfSellThisDay, buyDayProfit);
        }
        
        maxIfSellThisDay = max (   maxProfits[tradeNb-1][buyDay-1] + prices[day-1]      - prices[buyDay-1]) with buyDay<sellDay(day)
                         = max (   maxProfits[tradeNb-1][buyDay-1] - prices[buyDay-1] )   + prices[day-1]   with buyDay<sellDay(day)

        where max (maxProfits[tradeNb-1][buyDay-1] - prices[buyDay-1] ) is the max diff between maxProfig on buyday and price buyday
        
        so we can add this maxDiff in iteration to avoid this for loop:
        
        */
        vector<vector<int>> maxProfits(3, vector<int>(prices.size() + 1, 0));
        
        for(int tradeNb = 1; tradeNb<3;++tradeNb)
        {
            int maxDiff = INT_MIN;
            for(int day = 2; day<prices.size()+1; ++day)
            {
                maxDiff = max(maxDiff, maxProfits[tradeNb-1][day-2] - prices[day-2]);//---------> replace the for loop of all buy days
                const int maxIfSellThisDay = maxDiff + prices[day-1];
                
                const int ifNotTradeThisDay = maxProfits[tradeNb][day-1];
                
                maxProfits[tradeNb][day] = max(maxIfSellThisDay, ifNotTradeThisDay); 
                //cout<<"tradeNb : "<<tradeNb<< " day:"<< day<<" maxDiff:"<<maxDiff<< " maxprofit : "<<maxProfits[tradeNb][day]<<endl;
            }
        }
        return  maxProfits[2][prices.size()];
    }
    
    int maxProfit_DP(const vector<int>& prices) 
    {
        /*
        the duplication of the brute force is on the recomputations, how to do better ?
        think about DP solutions --> recusive call --> with memory cache --> memory structure is the tablution
        
        here 
        */
        
        vector<vector<int>> maxProfits(3, vector<int>(prices.size() + 1, 0));
        for(int tradeNb = 1; tradeNb<3;++tradeNb)
        {
            for(int day = 1; day<prices.size()+1; ++day)
            {
                const int ifNotTradeThisDay = maxProfits[tradeNb][day-1];
                int maxIfSellThisDay = 0;
                for(int buyDay = 1; buyDay < day; ++buyDay)
                {
                    const int buyDayProfit = maxProfits[tradeNb-1][buyDay-1] + prices[day-1] - prices[buyDay-1];
                    maxIfSellThisDay = max(maxIfSellThisDay, buyDayProfit);
                }
                
                maxProfits[tradeNb][day] = max(maxIfSellThisDay, ifNotTradeThisDay); 
            }
        }
        return  maxProfits[2][prices.size()];
    }

    int maxProfit_DP_bottom_up(const vector<int>& prices) {
        const auto n = prices.size();

        vector<int> firstBuy(n);
        vector<int> firstSell(n);
        vector<int> firstHold(n);
        vector<int> secondBuy(n);
        vector<int> secondSell(n);
        vector<int> secondHold(n);
        vector<int> wait(n);

        firstBuy[0] = -pirce[0];
        firstSell[0] = firstHold[0] = secondBuy[0] = secondHold[0] = secondSell[0] = INT_MIN;
        wait[0] = 0;
        
        for(int i=0; i<n, ++i){
            firstBuy[i] = wait[i-1] - parices[i];
            firstHold[i] = max(firstBuy[i-1], firstHold[i-1]);
            firstSell[i] = max(firstBuy[i-1], firstHold[i-1])+prices[i];
            secondBuy[i] = max(wait[i-1], firstSell[i-1]) - prices[i];
            secondHold[i]= max(secondBuy[i-1], secondHold[i-1]);
            secondSell[i] = max(secondBuy[i-1], secondHold[i-1]);
            wait[i] = max(wait[i-1], fristSell[i-1], secondSell[i-1]);
        }

        return max(max(secondSell[n-1], firstSell[n-1]), wait[n-1]);

    
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
