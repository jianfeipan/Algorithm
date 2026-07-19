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
#include <map>
#include <queue>

using namespace std;

/*
现有两种运算方式: 乘二或除三。输入一个target数，
输出从1开始如何运用两种运算得到target。如target=10，则可以1*2*2*2*2/3*2 = 10，输出**** / *
*/


string reachTargetx2OrDivid3(int target)
{
    int current = 1;
    queue<pair<int, string>> results;
    results.push({1,""});
    string operations;
    while(!results.empty())
    {
        const auto &  current = results.front();results.pop();
        if(current.first == target) return current.second;
        
        results.push({current.first*2, current.second+"*"});
        if(current.first/3!= 0) results.push({current.first/3, current.second+"/"});
    }
    return "not found";
}



int main(int argc, char *argv[])
{
    cout<<reachTargetx2OrDivid3(2)<<endl;
    cout<<reachTargetx2OrDivid3(4)<<endl;
    cout<<reachTargetx2OrDivid3(10)<<endl;
    return 0;
}
