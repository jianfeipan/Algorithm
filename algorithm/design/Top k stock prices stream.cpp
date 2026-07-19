

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include <unordered_set>
#include <stdexcept>
#include <deque>
#include <queue>
#include <limits.h>

using namespace std;

/*
receiving <Stock Price> stream
    currentPrice（String name）返回该股票的当前价格，
    currentProfit（String name）返回该股票目前的利润（其实就是当前价格减去起始价格），top20:
    返回当前利润最大的20个股票/
    股票价格变动次数最多的10个公司/
    当前历史最高股价排名前k高的公司和他的最高股价。    
*/
struct PriceMetric
{
    PriceMetric():
    max(0),
    changeCount(0),
    prices(),
    profit(0),
    topProfitIndex(-1),
    topPriceIndex(-1),
    topChangeIndex(-1)
    {}
    
    double max;
    size_t changeCount;
    vector<double> prices;
    double profit;
    int topProfitIndex;
    int topPriceIndex;
    int topChangeIndex;
};


class StockPrices
{
public:

    StockPrices(size_t k){_k = k;}
    
    void record(const string & stock, double price)
    {
        auto & priceMetrics = _prices[stock];
        auto & prices = priceMetrics.prices;
        prices.push_back(price);
        if(prices.size()>1 && prices.back() !=prices[prices.size() - 2]) ++priceMetrics.changeCount;
        rankNewProfit(stock);
        
        if(priceMetrics.max < price)
        {
            priceMetrics.max = max(priceMetrics.max, price);
            //rankNewMaxPrice(stock);
        }       
        //rankNewChangeCount(stock);
        
        

    }

    double currentPrice(const string & stock)
    {
        if(!_prices.count(stock)) throw invalid_argument("unknow stock name.");
        
        return  _prices[stock].prices.back();
    }
    
    double currentProfit(const string & stock)
    {
        if(!_prices.count(stock)) throw invalid_argument("unknow stock name.");
        
        return  _prices[stock].prices.back() - _prices[stock].prices.front();
    }
    
    vector<string> topProfits()
    {
        return {};
    }
    
    vector<string> topPariceChange()
    {
        return {};   
    }
    
    vector<pair<string, double>> topPrices()
    {
        return {};
    }
    
private:
    void rankNewProfit(const string & stock)
    {
        auto & metrics = _prices[stock];
        if(metrics.topProfitIndex==-1)
        {
            metrics.topProfitIndex = topCurrentProfits.size();
            topCurrentProfits.push_back(stock);
        }
        
        for(int i = metrics.topProfitIndex; i>=1; --i)
        {
            if(_prices[topCurrentProfits[i]].profit > _prices[topCurrentProfits[i-1]].profit)
            {
                auto temp = topCurrentProfits[i-1];
                topCurrentProfits[i-1] = topCurrentProfits[i];
                topCurrentProfits[i] = temp;
                
                _prices[topCurrentProfits[i-1]].topProfitIndex = i-1;
                _prices[topCurrentProfits[i]].topProfitIndex = i;
            }
            else break;
        }
        
        if(topCurrentProfits.size() > _k)
        {
            _prices[topCurrentProfits.back()].topProfitIndex = -1;
            topCurrentProfits.pop_back();
        }
    }

    
private:
    size_t _k;

    unordered_map<string, PriceMetric> _prices;
    
    vector<string> topCurrentProfits;
    vector<string> topHistoryPrices;
    vector<string> topPriceChanges;
};


int main(int argc, char *argv[])
{  
    
    return 0;
}
