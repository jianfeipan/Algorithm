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
    _timeLine()
    {
    }

    void addAvilibility(int start, int end) 
    {
        ++_timeLine[start];
        --_timeLine[end];
        
    }
    
    bool isAviliable(int from, int to) 
    {
        if(from>to) throw invalid_argument("input time interval is not valid");
        
        int avilibility= 0;
        for(int i = from; i<= to; ++i)
        {
            avilibility+=_timeLine[i];
            if(avilibility<1) return false;
        }
        
        return true;
    }
       
private:
    array<int, 23> _timeLine;//if we check only 24 hours, with only hour check, non minutes O(1) for add, and O(RANGE) for read
    map<int, int> _TreeMapTimeLine;// can use treemap to do with minutes O(logN) for add, O(RANGE*logN) for read
    
    vector<pair<int, int>> _invervals;// merge interval : O(RANGE), find O(logN) by using binary search
    /*can be replaced by :*/
    map<int, int> _treeMapInterVal;//map.lower_bound [)  : first element not less than; upper_bound : first e not bigger than
};


int main()
{
   
}
