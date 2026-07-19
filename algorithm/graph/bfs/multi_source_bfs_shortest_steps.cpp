class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        { 0,-1},
        { 0, 1},
        {-1, 0},
        { 1, 0}
    }};

public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        // the distance to its nearest treasure chest. -. 
        // BFS -> shortest steps
        using Row = int;
        using Col = int;
        queue<pair<Row, Col>> q;

        const auto R = grid.size();
        const auto C = grid[0].size();
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){ // Multi source BFS!!!
                if(grid[r][c] == 0) q.push({r,c}); // no need to have visited, the values itself is not INT_MAX means visited
            }
        }

        auto valid = [&](int row, int col){
            if(row<0 || row>=R || col<0 || col>=C) return false;
            if(grid[row][col]== -1) return false;
            return true;
        };

        while(!q.empty()){
            auto level_size = q.size();
            for(int i = 0; i<level_size; ++i){
                auto [row, col] = q.front(); q.pop();
                for(auto [dr, dc] : DIRECTIONS){
                    auto newR = row + dr;
                    auto newC = col + dc;
                    if(valid(newR, newC)){
                        if(grid[newR][newC] == INT_MAX ){
                            grid[newR][newC] = grid[row][col] + 1;
                            q.push({newR, newC});
                        }
                    }
                }
            }
        }
    }
};
