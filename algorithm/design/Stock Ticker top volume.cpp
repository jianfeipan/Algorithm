#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>
#include <list>
#include <set>
#include <map>

using namespace std;

/*
Stock Ticking (similar to Leaderboard)
Implement the following two functions such that they are optimal. 

addStocksVolume receives a symbol (INTC, APPL, etc) plus a volume which you cumulate over time.
topKstocks would return the k stocks with the highest volume.
void addStocksVolume(string stockSymbol, int volume) {

}

vector<string> topKstocks(int k) {
    // return k top stocks 
}

*/
class StockTicker 
{
    
public: 
    StockTicker()
    {
    }

    void addStocksVolume(const string &  stock, size_t volume) 
    {
        auto it = _volumes.find(stock);
        if(it != _volumes.end())
        {
            _rank[it->second].erase(stock);
            it->second += volume;
            _rank[it->second].insert(stock);
        }
        else 
        {
            _volumes[stock] = volume;
            _rank[volume].insert(stock);
        }
    }
    
    vector<string> topKstocks(size_t k) // can we allow k>stock size
    {
        vector<string> topK;topK.reserve(k);
        for(const auto & stocksInSameRank : _rank)
        {
            for(const auto & stock : stocksInSameRank.second)
            {
                topK.push_back(stock);
                if(topK.size()==k) return topK;
            }
        }
        
        return topK;
    }
       
private:
//as the k could be any size, we need store all stocks
//best way is to keep them in order of volume

    unordered_map<string, size_t> _volumes;
    map<size_t, set<string>, greater<size_t>> _rank;
   
};

void print(const vector<string> & rank)
{
    for(const auto & stock : rank) cout<<stock<<", ";
    cout<<endl;
}

int main()
{
    StockTicker tracker;
    tracker.addStocksVolume("APPL", 100);print(tracker.topKstocks(5));
    tracker.addStocksVolume("APPL", 200);print(tracker.topKstocks(5));
    tracker.addStocksVolume("META", 500);print(tracker.topKstocks(5));
    tracker.addStocksVolume("AMZN", 400);print(tracker.topKstocks(5));
    tracker.addStocksVolume("DDOG", 1000);print(tracker.topKstocks(5));
}
