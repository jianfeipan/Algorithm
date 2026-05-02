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
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Reorder Array
Consider a vector of employees with a name and their title: <John, Manager>. 

And a dictionary where the keys report to the values: [CTO, CEO].

Re-order the vector of employees according to the dictionary mappings. The vector of employees can be extremely big, however the dictionary only contains the title orderings.
vector : [<John, Manager>, <Sally, CTO>, <Sam, CEO>, <Drax, Engineer>, <Bob, CFO>, <Daniel, Engineer>]
dict: {[CTO, CEO], [Manager, CTO], [Engineer, Manager], [CFO, CEO]}

output:
[<Drax, Engineer>, <Daniel, Engineer>, <John, Manager>, <Sally, CTO>, <Bob, CFO>, <Sam, CEO>]

*/

using Title = pair<string, string>;

vector<Title> sort(const unordered_map<string, string> & reportOrder, const vector<Title> & titles)
{
    unordered_map<string, set<string>> namesByTitles;
    for(const auto & title : titles) namesByTitles[title.second].insert(title.first);
 
    unordered_map<string, set<string>> waitForReport;
    for(const auto & reportTo : reportOrder) waitForReport[reportTo.second].insert(reportTo.first);
    
    
    vector<Title> sorted;sorted.reserve(titles.size());
    while(!namesByTitles.empty())
    {
        string wiatForNoBody;
        for(const auto & [title, reportTo]: namesByTitles)
        {
            if(waitForReport[title].size() == 0)
            {
                wiatForNoBody = title;
                break;
            }
        }
        
        if(wiatForNoBody.empty()) throw invalid_argument("input report order has cicyle.");
        
        auto it  = reportOrder.find(wiatForNoBody);
        if(it!=reportOrder.end()) waitForReport[it->second].erase(wiatForNoBody);
        
        for(const auto & name : namesByTitles[wiatForNoBody])
            sorted.push_back({name, wiatForNoBody});
            
        namesByTitles.erase(wiatForNoBody);
    }
    return sorted;
}

int main()
{
    const auto & titles = sort(
        {
            {"CTO", "CEO"},
            {"Manager", "CTO"},
            {"Engineer", "Manager"},
            {"CFO", "CEO"}
        },
        {
          {"John", "Manager"}, {"Sally", "CTO"}, {"Sam", "CEO"}, {"Drax", "Engineer"}, {"Bob", "CFO"}, {"Daniel", "Engineer"}  
        }
    );     
    for(const auto & title : titles) cout<<title.first<<","<<title.second<< "  -> ";
    cout<<endl;
}
