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
cclass Solution {
// singles source shortest path: Dijkstra
private:
    constexpr static array<pair<int, int>, 4> DIRECTIONS = {{
        { 1,0},
        {-1,0},
        {0, 1},
        {0,-1}
    }};

public:
    int swimInWater(vector<vector<int>>& grid) {
        const auto R = grid.size();
        const auto C = grid[0].size();

        vector<vector<int>> min_path(R, vector<int>(C, INT_MAX));
        using Node = tuple<int, int, int>;
        priority_queue<Node, vector<Node>, greater<>> minHeap;

        // start from left top corner   
        minHeap.push({grid[0][0], 0, 0});

        while(!minHeap.empty()){
            auto [w, r, c] = minHeap.top();minHeap.pop();
            if(w > min_path[r][c]) continue; // skip I already has smaller

            for(const auto& [dr, dc] : DIRECTIONS){
                auto next_r = r+dr;
                auto next_c = c+dc;
                if(0<=next_r && next_r < R && 0<=next_c && next_c<C){
                    auto next_w = max(w, grid[next_r][next_c]);// instead of sum, this is MAX
                    if(next_w < min_path[next_r][next_c]) {
                        min_path[next_r][next_c] = next_w;
                        minHeap.push({next_w, next_r, next_c});
                    }
                }
            }
        }

        return min_path[R-1][C-1];
    }
};


