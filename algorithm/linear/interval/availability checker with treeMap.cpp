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
#include <array>

using namespace std;

/*
Stock Exchange System
Given a list of operation hour for each stock exchange,
 validate if the customer can send a trading order during the input hour. 
 list all possible solutions that I got and explain the time and space complexity of each solution. 
 describe the advantages and disadvantages of each one.
// Example 
Operation hours
09:00-16:00 Royal Bank of Scotland
11:00-17:00 Morgan Stanley
 
Test case #1 - expected result: SUCCESS
10:00-17:00

Test case #2 - expected result: FAILURE
15:00-21:00
*/
class AvilibilityChecker 
{
    
public: 
    AvilibilityChecker():
    _aviliablities()
    {
    }

    void addAvilibility(int start, int end) 
    {
        cout<<"insert"<<start<<", "<<end<<endl;
        if(start>end) throw invalid_argument("input time interval is not valid");
        
        if(_aviliablities.empty() || end<_aviliablities.begin()->first || _aviliablities.rbegin()->second < start) _aviliablities[start] = end;
        else 
        {
            auto startIt = _aviliablities.lower_bound(start);
            auto endIt = _aviliablities.upper_bound(end);
            
            if(startIt!=_aviliablities.begin())
            {
                auto prev = startIt;--prev;
                if(prev->second>=start)
                {
                    startIt=prev;
                    start = prev->first;
                }
            }
            cout<<"endIt"<<endIt->first<<endl;
            if(endIt!=--_aviliablities.end())
            {
                auto next = endIt;++next;cout<<"next"<<next->first<<endl;
                if(next->first<=end)
                {
                    end = max(end, next->second);
                    endIt = next;
                }
                else 
                {
                    end = max(end, endIt->second);
                }
            }
            
            _aviliablities.erase(startIt,++endIt);
                        
            _aviliablities[start] = end;
        }
        
    }
    
    bool isAviliable(int from, int to) 
    {
        for(const auto & [from, to] : _aviliablities)cout<<"["<<from<< ", "<<to<<"]";
        cout<<endl;

        if(from>to) throw invalid_argument("input time interval is not valid");
        
        auto it = _aviliablities.find(from);
        if(it!=_aviliablities.end()) return to<=it->second;
        
        auto upper = _aviliablities.upper_bound(from);
        if(upper!=_aviliablities.end()) return to<=upper->second;
        
        return false;
    }
       
private:
    map<int, int> _aviliablities;//map.lower_bound [)  : first element not less than; upper_bound : first e smaller than
};


int main()
{
   AvilibilityChecker checker;
   checker.addAvilibility(1, 3);
   checker.addAvilibility(2, 4);cout<<checker.isAviliable(1,4)<<endl;//1-4
   checker.addAvilibility(5, 7);cout<<checker.isAviliable(3,6)<<endl;
   checker.addAvilibility(1, 10);cout<<checker.isAviliable(2,9)<<endl;
   checker.addAvilibility(0, 2);cout<<checker.isAviliable(1,10)<<endl;
}
