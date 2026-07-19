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

TV Show
A TV show is "addictive" if the viewers quickly become addicted to the show and eventually finish watching the show. 

It can be tracked after viewing 
            how many episodes of a show 
                at least 70% of the viewers who watched that
                    continued on to finish the show entirely.
                    
                    
In other words, more that 70% of the viewers who watched the first x eposides of a show continued on to finish the entire show. 
The x is what we are looking for.
Assumptions:
All shows have 10 episodes
viewers always start from the first episode (no skipping).
Given a log of entries consisting of a user id, the show name and the episode number that was watched, 
produce the x for each show.
// example 
Input: The following function is called for each log entry
void process_log(string show, int episode, int user_id)

? can user be duplicated?-->unique count is the real

Expected Output:
void print_results();
*/

class TVShowAnalyzer
{
public:
    void process_log(string show, int episode, int user_id)
    {
        _records[show][episode].insert(user_id);
    }
    
    unordered_map<string, int> computeX()
    {
        unordered_map<string, int> xValues;
        
        /*
        0       1       2       3    4   5   6   7   8   9
                120      110    100   90                 70
        
        */
        
        for(const auto & [name, metric]: _records)
        {
            int finishedCount = metric.rbegin()->second.size();
            
            int xEpMinCount = ceil((double)finishedCount/0.7);
            
            int x = -1;
            for(const auto & episod : metric)
            {
                if(episod.second.size() >= xEpMinCount) x = episod.first;
                else break;
            }
            
            xValues[name] = x;
        }
        
        return xValues;
    }
private:
    unordered_map<string, map<int, unordered_set<int>>> _records; 
    
};



int main()
{
    
    
    cout<< maxSumAndPath.first<<endl;
    for(const auto & node : maxSumAndPath.second) cout<<node<<", ";
    cout<<endl;
}
