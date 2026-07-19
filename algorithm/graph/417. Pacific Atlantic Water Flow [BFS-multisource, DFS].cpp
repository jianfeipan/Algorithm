/*
You are given a rectangular island heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The islands borders the Pacific Ocean from the top and left sides, and borders the Atlantic Ocean from the bottom and right sides.

Water can flow in four directions (up, down, left, or right) from a cell to a neighboring cell with height equal or lower. Water can also flow into the ocean from cells adjacent to the ocean.

Find all cells where water can flow from that cell to both the Pacific and Atlantic oceans. Return it as a 2D list where each element is a list [r, c] representing the row and column of the cell. You may return the answer in any order.

Example 1:



Input: heights = [
  [4,2,7,3,4],
  [7,4,6,4,7],
  [6,3,5,3,6]
]

Output: [[0,2],[0,4],[1,0],[1,1],[1,2],[1,3],[1,4],[2,0]]
Example 2:

Input: heights = [[1],[1]]

Output: [[0,0],[1,0]]
Constraints:

1 <= heights.length, heights[r].length <= 100
0 <= heights[r][c] <= 1000
*/
class Solution {
// from boarders do bfs/dfs, stop when it goes down: water cannot flow
// mark visited by +1 and they other +1, 
// the cells with 2 are the answers.
private:
    vector<pair<int, int>> directions = {
        {-1, 0},
        { 1, 0},
        {0, -1},
        {0,  1}
    };

private:
    void bfs(queue<pair<int, int>>& q, int R, int C, 
            vector<vector<int>>& visited, 
            const vector<vector<int>>& heights){
        //BFS
        while(!q.empty()){
            const int size = q.size();
            for(int i=0; i<size; ++i){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                // go up to unvisited & higher neighbors
                for(const auto& direction : directions){
                    int nr = r+direction.first;
                    int nc = c+direction.second;
                    if(nr>=0 && nr<R
                    && nc>=0 && nc<C
                    && visited[nr][nc] == 0
                    && heights[nr][nc] >= heights[r][c]){
                        ++visited[nr][nc];
                        q.push({nr, nc});
                    }
                }
            }
        }
    }
public:
    // multi-source BFS
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const int R = heights.size();
        const int C = heights[0].size();

        vector<vector<int>> visited_from_left_top(R, vector<int>(C, 0));
        {
            queue<pair<int, int>> q;
            //left border
            for(int r=0; r<R; ++r){
                visited_from_left_top[r][0] = 1;
                q.push({r, 0});
            }
            //top border
            for(int c=0; c<C; ++c){
                visited_from_left_top[0][c] =1 ;
                q.push({0, c});
            }
            bfs(q, R, C, visited_from_left_top, heights);
        }

        vector<vector<int>> visited_from_right_bottom(R, vector<int>(C, 0));
        {
            queue<pair<int, int>> q;
            //right border
            for(int r=0; r<R; ++r){
                visited_from_right_bottom[r][C-1] = 1;
                q.push({r, C-1});
            }
            //bottom border
            for(int c=0; c<C; ++c){
                visited_from_right_bottom[R-1][c] = 1;
                q.push({R-1, c});
            }
            bfs(q, R, C, visited_from_right_bottom, heights);
        }

        vector<vector<int>> cells;
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                if(visited_from_left_top[r][c] && visited_from_right_bottom[r][c]){
                    cells.push_back({r, c});
                }
            }
        }
        return cells;
        
    }
};
