class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        { 0,-1},
        { 0, 1},
        {-1, 0},
        { 1, 0}
    }};
    
    void dfs_mark_island(int r, int c, vector<vector<int>>& grid, int& area){
        const auto R = grid.size();
        const auto C = grid[0].size();
        if(r<0 || r>= R || c<0 || c>= C) return;
        auto cur = grid[r][c];
        if(cur == 1){
            grid[r][c] = -1;
            ++area;
            for(const auto& [dr, dc] : DIRECTIONS) dfs_mark_island(r+dr, c+dc, grid, area);
        }
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
                const auto R = grid.size();
        const auto C = grid[0].size();
        int maxArea = 0;

        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                if(grid[r][c] == 1){
                    int area = 0;
                    dfs_mark_island(r, c, grid, area);
                    maxArea = max(maxArea, area);
                }
            }
        }
        return maxArea;
    }
};
