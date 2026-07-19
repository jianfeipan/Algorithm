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

using namespace std;

/*
Elements in first but not in Second
Return the strings having characters that are not present in another string
// example 
string a - "abcd"
string b - "ab"

ans - "cd"

}

*/

string diffFrom(string inclu, string exclu)
{
    string diffs;
    
    sort(inclu.begin(), inclu.end());
    sort(exclu.begin(), exclu.end());
    
    size_t left = 0;
    size_t right = 0;
    while(left < inclu.size() && right<exclu.size())
    {
        if(inclu[left] < exclu[right]) 
        {
            diffs+=inclu[left];
            ++left;
        }
        else if(inclu[left] == exclu[right]) 
        {
            ++left; ++right;
        }
        else
        {
            ++left;
        }
    }
    
    if(left < inclu.size())
    {
        diffs+=inclu.substr(left);    
    }
    return diffs;
}

int main()
{
    cout<< diffFrom("abcdefg", "acf");
 
}
