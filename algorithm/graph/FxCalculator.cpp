#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

/*
Evaluate Division
Array of currency conversion rates. E.g. ['USD', 'GBP', 0.77] which means 1 US is equal to 0.77 GBP an array containing a 'from' currency and a 'to' currency. Given the above parameters, find the conversion rate that maps to the 'from' currency to the 'to' currency. Your return value should be a number
// Example:
You are given the following parameters:
Rates: ['USD', 'JPY', 110] ['USD', 'AUD', 1.45] ['JPY', 'GBP', 0.0070]
From/To currency: ['GBP', 'AUD']
Output: 1.89

*/
struct FxRate
{
    string from;
    string to;
    double rate;
};

class FxCalculator
{
public:
    FxCalculator(const vector<FxRate> & fxRates)
    {
        for(const auto & fxRate : fxRates)
        {
            _fxRates[fxRate.from][fxRate.to] = fxRate.rate;
            _fxRates[fxRate.to][fxRate.from] = 1./fxRate.rate;
        }
    }

    double computeFxRate(const string & from, const string  & to)
    {
        queue<pair<string, double>> level;
        unordered_set<string> visited;
        
        visited.insert(from);
        level.push({from, 1.});
        while(!level.empty())
        {
            const auto & current = level.front();
            if(current.first == to) return current.second;
            
            for(const auto & [toCurrency, rate] : _fxRates[current.first])
            {
                if(visited.count(toCurrency) == 0) 
                {
                    visited.insert(toCurrency);
                    level.push({toCurrency, rate * current.second});
                }
            }
            level.pop();
        }
        
        //throw invalid_argument("this currency pair exchange is not supported.");
        return 0.;
    }
private:
  unordered_map<string, unordered_map<string, double>> _fxRates;  

};


int main()
{
    FxCalculator fxCalculator({
        {"USD", "JPY", 110},
        {"USD", "AUD", 1.45},
        {"JPY", "GBP", 0.0070}
    });
    
    cout<< fxCalculator.computeFxRate("GBP", "AUD");
}
