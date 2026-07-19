/*
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
*/

#include<array>

class Solution {
// BFS multi-source
private:
 constexpr static array<pair<int, int>, 4> directions = {{
        { 1,0},
        {-1,0},
        {0, 1},
        {0,-1}
    }};
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int freshNum = 0;
        for(int r=0; r<grid.size(); ++r){
            for(int c=0; c<grid[r].size(); ++c){
                if(grid[r][c] == 2){
                    q.push({r,c});
                }else if(grid[r][c] == 1){
                    ++freshNum;
                }
            }
        }

        int t = 0;
        while(freshNum>0 && !q.empty()){
            //one level
            const int size = q.size();
            for(int i=0; i<size; ++i){
                auto [r, c] = q.front(); q.pop();

                for(const auto& [dr, dc] : directions){
                    auto nr = r+dr;
                    auto nc = c+dc;
                    if( nr>=0 && nr<grid.size() 
                    && nc>=0 && nc<grid[nr].size()
                    && grid[nr][nc] == 1){
                        q.push({nr, nc});
                        grid[nr][nc] =2; // visited!
                        --freshNum;
                    }
                }
            }
            ++t;
        }
        
        return freshNum == 0 ? t : -1;
    }
};

