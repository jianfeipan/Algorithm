#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>
#include <sstream>
#include <stack>

using namespace std;
/*
Implement a class called AirMap that has two methods:
1. add_route(start, destination) - adds ONE WAY connecting flight from one airport to another
2. print_all_routes(start, destination) - prints all possible routes from start to destination

Given the following routes, print all possible routes between the airport C and D:
A -----> B
B -----> A
A -----> C
C -----> A
A -----> D
D -----> A
B -----> C
C -----> B
B -----> D
D -----> B
Expected Output:
C,A,B,D
C,A,D
C,B,A,D
C,B,D
*/
class AirLines{
public:    
    void addRoute(const string & start, const string & end)
    {
        _destinations[start].insert(end);
    }
    
    vector<vector<string>> printAllRoutes(const string & start, const string & end)
    {
        vector<vector<string>> routes;
        
        stack<string> nodes;
        for(const auto & destination : _destinations[start])    
        {    
            unordered_set<string> visited;
            dfsSearch(destination, end, visited, {start}, routes);
        }
        return routes;
    }
    
private:
    void dfsSearch(const string & current, const string & end,  unordered_set<string> visited, vector<string> currentPath, vector<vector<string>> & routes)
    {
        if(visited.count(current)) return;
        
        visited.insert(current);
        currentPath.push_back(current);
        
        if(current == end) 
        {
            routes.push_back(currentPath);
            return ;
        }
        
        for(const auto & destination : _destinations[current])    
        {    
            dfsSearch(destination, end, visited, currentPath, routes);
        }        
    }

    
private:
    unordered_map<string, unordered_set<string> > _destinations;
};


int main()
{
    AirLines airLines;
    airLines.addRoute("A", "B");
    airLines.addRoute("B", "A");
    airLines.addRoute("C", "A");
    airLines.addRoute("A", "D");
    airLines.addRoute("D", "A");
    airLines.addRoute("B", "C");
    airLines.addRoute("C", "B");
    airLines.addRoute("B", "D");
    airLines.addRoute("D", "B");
    
    const auto & routes = airLines.printAllRoutes("C", "D");
    
    for(const auto & route : routes)
    {
        for(const auto & stop : route) cout<< stop<<">";
        cout<<endl;
        
    }
    
    return 0;
}
