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

Maximum paths in N steps
Given 2d matrix, find maximum path sum in given N steps only
// example 
2, 3, 4, 6
1, 2, 3 ,5
3, 4, x ,5
0, 1, 2, 3
N = 2
starting cordinate = (2,2)
N = 2
Output: 10 (5->5)


*/

using Sum = int;
using Path = vector<int>;
using Point = pair<int, int>;
struct Node
{
    int lin;
    int col;
    Sum sum;
    Path path;
    set<Point> visited;
};

static const vector<Point> directions = {
    {-1, 0},
    { 1, 0},
    { 0, 1},
    { 0,-1}
};


pair<Sum, Path> findMaxSumPath(const vector<vector<int>> & matrix, int step, int startLine, int startCol)
{
    //idea: cannot use greed, because we could lose the max
    //      use BFS for step 
    if(matrix.empty() || matrix[0].empty()) throw invalid_argument("Empty matrix is not supported");//return 0;
    
    const size_t linCount = matrix.size();
    const size_t colCount = matrix[0].size();
        
    queue<Node> level;
    Node startNode = {startLine, startCol, 0,{matrix[startLine][startCol]}, {{startLine, startCol}}};
    level.push(startNode);
    
    while(step-->0 && !level.empty())
    {
        const size_t size = level.size();
        for(size_t i = 0; i<size; ++i)
        {
            const auto & current = level.front();
            
            for(const auto & dir : directions)
            {
                const int newLin = current.lin+dir.first;
                const int newCol  = current.col+dir.second;
                
                if(0<=newLin && newLin < linCount 
                && 0<=newCol && newCol < colCount)
                {
                    if(current.visited.count({newLin, newCol}) == 0)
                    {
                        Node newNode = current;
                        newNode.lin = newLin;
                        newNode.col = newCol;
                        newNode.sum += matrix[newLin][newCol];
                        newNode.path.push_back(matrix[newLin][newCol]);    
                        newNode.visited.insert({newLin, newCol});
                        level.push(newNode);
                    }
                }
            }
            
            level.pop();
        }
    }
    
    //level reste only the last level
    int maxSum = 0;
    Path maxPath;
    while(!level.empty())
    {
        const auto & current = level.front();
        
        if(maxSum < current.sum)
        {
            maxSum = current.sum;
            maxPath = current.path;
        }    
            
            
        level.pop();
        
    }
    
    return {maxSum, maxPath};
}


int main()
{
    const auto & maxSumAndPath = findMaxSumPath(
        {
            {   100,    3,   100,     6},
            {   1,      2,   1 ,      5},
            {   3,      1,   0 ,      5},
            {   0,      1,   1,       3},
        }, 4 , 2, 2
    );
    
    cout<< maxSumAndPath.first<<endl;
    for(const auto & node : maxSumAndPath.second) cout<<node<<", ";
    cout<<endl;
}
