/*
You are given a square 2-D matrix of distinct integers grid where each integer grid[i][j] represents the elevation at position (i, j).

Rain starts to fall at time = 0, which causes the water level to rise. At time t, the water level across the entire grid is t.

You may swim either horizontally or vertically in the grid between two adjacent squares if the original elevation of both squares is less than or equal to the water level at time t.

Starting from the top left square (0, 0), return the minimum amount of time it will take until it is possible to reach the bottom right square (n - 1, n - 1).

Example 1:
Input: grid = [[0,1],[2,3]]

Output: 3
Explanation: For a path to exist to the bottom right square grid[1][1] the water elevation must be at least 3. At time t = 3, the water level is 3.

Example 2:



Input: grid = [
  [0,1,2,10],
  [9,14,4,13],
  [12,3,8,15],
  [11,5,7,6]
]

Output: 8
Explanation: The water level must be at least 8 to reach the bottom right square. The path is [0, 1, 2, 4, 8, 7, 6].

Constraints:

grid.length == grid[i].length
1 <= grid.length <= 50
0 <= grid[i][j] < n^2
*/

/*
lowest cost from start to end
hights are cost

Dijkstra's minimum spanning tree:
 from one point
 global cost to all other nodes,
 take the closes, update it
 until the end is connected.

*/
#include <array>
class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        {1, 0},
        {-1, 0},
        {0, -1},
        {0, 1}
    }};
public:
    int swimInWater(vector<vector<int>>& grid) {
        const auto& R=grid.size(); if(R==0) return -1; // invalid input
        const auto& C=grid[0].size(); if(C==0) return -1; // invalid input

        // vector<vector<int>> distance(R,vector<int>(C, INT_MAX));
        // distance[0][0] = 0;

        using Cost = int;
        using Row = int;
        using Col = int;
        using Edge = tuple<Cost, Row, Col>;
        priority_queue<Edge, vector<Edge>, greater<Edge>> frontier;

        vector<vector<bool>> visited(R, vector<bool>(C, false));
        
        
        visited[0][0]=true;
        frontier.push({grid[0][0], 0, 0});
        while(!frontier.empty()){
            const auto [minCost, r, c] = frontier.top(); frontier.pop();
            if(r==R-1 && c==C-1) return minCost; // distance = min(distance, minCost)

            for(const auto&[dr, dc] : DIRECTIONS){
                auto newR = r+dr;
                auto newC = c+dc;
                if(newR>=0 && newR<R
                && newC>=0 && newC<C && !visited[newR][newC]){
                    visited[newR][newC]=true;
                    frontier.push({max(grid[newR][newC], minCost), newR, newC});
                }
            }
        }
        //O(n^2 * logn)
        return -1;
    }
};

