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
        const auto n_row = grid.size();
        const auto n_col = grid[0].size();
        // multi source BFS
        using Row = int;
        using Col = int;
        queue<pair<Row, Col>> bfs;
        for (int r=0; r<n_row; ++r) {
            for (int c=0; c<n_col; ++c) {
                if (grid[r][c] == 0) {
                    bfs.push({r, c});
                }
            }
        }

        int step = 1;
        while (!bfs.empty()) {
            const auto size = bfs.size();
            for(int i = 0; i<size; ++i) {
                auto [r, c] = bfs.front();bfs.pop();

                for(auto [dr, dc] : DIRECTIONS) {
                    auto next_r = r+dr;
                    auto next_c = c+dc;

                    if (0 <= next_r && next_r < n_row &&
                        0 <= next_c && next_c < n_col &&
                        grid[next_r][next_c] == INT_MAX) {
                        
                        grid[next_r][next_c] = step;// !!!should mark as visited, avoid multi source push the same
                        bfs.push({next_r, next_c});
                    }
                }
            }

            ++step;
        }
    }
};
