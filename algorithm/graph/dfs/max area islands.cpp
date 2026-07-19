class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        { 0,-1},
        { 0, 1},
        {-1, 0},
        { 1, 0}
    }};
    
    void visit_island(vector<vector<int>>& grid, 
                      int r, int c, 
                      int& area) {
        const auto R = grid.size();
        const auto C = grid[0].size();
        if(r<0 || r>=R || c<0 || c>= C) return;
        if(grid[r][c] == 0) return;

        ++area;
        grid[r][c] = 0; // visited
        
        for(const auto& [dr, dc] : DIRECTIONS) {
            visit_island(grid, r+dr, c+dc, area);
        }
    }
   
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const auto R = grid.size();
        const auto C = grid[0].size();
        int maxArea = 0;

        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                int area = 0;
                visit_island(grid, r, c, area);

                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};

