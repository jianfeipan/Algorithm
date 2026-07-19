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
Delete Array in Range
Remove ints from an array from given ranges.
Example:

Input: array = {-8, 3, -5, 1, 51, 56, 0, -5, 29, 43, 78, 75, 32, 76, 73, 76}, 
ranges = {{5, 8}, {10, 13}, {3, 6}, {20, 25}}
Output: {-8, 3, -5, 29, 43, 76, 73, 76}
*/

map<int, int> readRang(const vector<pair<int, int>> & ranges)//O(0)
{
    //....
    return {};
}


bool isInRange(int num, map<int, int> range)//O(n)
{
    auto it = range.upper_bound(num);
    return it->second>=num;
}



bool isInRange(int num, const set<int> starts, const set<int> & ends)//log(M)
{
    const int rightStarts = distance(starts.lower_bound(num), starts.end());
    const int rightEnds = distance(ends.lower_bound(num), ends.end());
    
    return rightStarts != rightEnds;
     
}

vector<int> clean(const vector<int> & nums, const vector<pair<int, int>> & ranges)
{
    
    set<int> starts;
    set<int> ends;
    
    for(const auto & range : ranges)
    {
        starts.insert(range.first);
        ends.insert(range.second);
    }
    
    vector<int> cleaned;
    
    for(const auto & num : nums)//O(NlogM + MlongM)
    {
        if(!isInRange(num, starts, ends))
        {
            cleaned.push_back(num);
        }
    }
    
    return cleaned;
}


int main()
{
    
    const auto & cleaned = clean({-8, 3, -5, 7, 21, 56, 24, 11, 8, 5, 7, 8, 76}, {{5, 8}, {10, 13}, {3, 6}, {20, 25}});     
    for(const auto & node : cleaned) cout<<node<<", ";
    cout<<endl;
}
