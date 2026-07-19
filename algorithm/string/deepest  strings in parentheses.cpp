#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*
 all the strings in the deepest level
e.g. (1(2{{3}})){{{{4}}}} return ["3", "4"]
*/

static const unordered_map<char, char> & openCloses()
{
    static unordered_map<char, char> openClose({
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    });
    return openClose;
}

static bool isAnOpen(char c)
{
    return openCloses().count(c);
}

static bool isAClose(const char & open, const char & close)
{
    auto it = openCloses().find(open);
    if(it!=openCloses().end())
        return close == it->second;    
    else 
        return false;
}


vector<string> deepestString(const string & setence)
{
    vector<string> deepest;
    
    stack<char> leftOpen;
    int maxDepth = 0;
    
    string current("");
    for(auto c : setence)
    {
        if(isAnOpen(c))
        {
            leftOpen.push(c);
            current.clear();
        }
        else if(isAClose(leftOpen.top(), c))
        {
            if(leftOpen.size() > maxDepth)
            {
                maxDepth = leftOpen.size();
                deepest.clear();
                deepest.push_back(current);
            }
            else if(leftOpen.size() == maxDepth)
            {
                deepest.push_back(current);
            }
            leftOpen.pop();
        }
        else 
        {
            current+=c;
        }
    }
    
    return deepest;
}


int main(int argc, char *argv[])
{
    const auto & deepest = deepestString("(1asd(2asd{{3asd}asd}asd)){{{{4asd}}}}");

    for(const auto & word : deepest) cout<<word<<", ";
    cout<<endl;

    return 0;
}
