/*
You are given a 2-D matrix board containing 'X' and 'O' characters.

If a continous, four-directionally connected group of 'O's is surrounded by 'X's, it is considered to be surrounded.

Change all surrounded regions of 'O's to 'X's and do so in-place by modifying the input board.

Example 1:



Input: board = [
  ["X","X","X","X"],
  ["X","O","O","X"],
  ["X","O","O","X"],
  ["X","X","X","O"]
]

Output: [
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","X","X","O"]
]
Explanation: Note that regions that are on the border are not considered surrounded regions.

Constraints:

1 <= board.length, board[i].length <= 200
board[i][j] is 'X' or 'O'.

*/

class Solution {
private:
    constexpr static array<pair<int, int>, 4> DIRECTIONS = {{
        { 1,0},
        {-1,0},
        {0, 1},
        {0,-1}
    }};

    void dfs_mark(
        int r, 
        int c, 
        vector<vector<int>>& marked, 
        const vector<vector<char>>& board){
        
        if(board[r][c] != 'O') return;

        auto valid = [&](int r, int c){
            const auto R = board.size();
            const auto C = board[0].size();
            if(r<0 || r>=R || c<0 || c>=C) return false;
            if(marked[r][c]) return false;

            return true;
        };
        
        marked[r][c] = 1;
        for(auto [dr, dc] : DIRECTIONS){
            auto new_r = r+dr;
            auto new_c = c+dc;
            if(valid(new_r,new_c)){
                if(board[new_r][new_c] == 'O'){
                    dfs_mark(new_r, new_c, marked, board);
                }
            }
        } 
    }
public:
    void solve(vector<vector<char>>& board) {
        const auto R = board.size();
        const auto C = board[0].size();

        vector<vector<int>> not_surranded(R, vector<int>(C, 0));
        for(int r=0; r<R; ++r){
            dfs_mark(r, 0, not_surranded, board);
            dfs_mark(r, C-1, not_surranded, board);
        }

        for(int c=1; c<C; ++c){
            dfs_mark(0, c, not_surranded, board);
            dfs_mark(R-1, c, not_surranded, board);
        }

        for(int r=1; r<R-1; ++r){
            for(int c=1; c<C-1; ++c){
                if(board[r][c] == 'O'){
                    if(!not_surranded[r][c]) board[r][c] = 'X';
                }
            }
        }
    }
};



class Solution_BFS {
private:
// bfs from boundries color the O's to ., 
// then scan all O->x, . to O
    constexpr static array<array<int, 2>, 4> DIRECTIONS {{
        { +1, 0},
        { -1, 0},
        { 0, +1},
        { 0, -1}
    }};

public:
    void solve(vector<vector<char>>& board) {
        const auto R = board.size();
        const auto C = board[0].size();
        // multi shource bfs
        queue<pair<int, int>> bfs;
        // push the for boundries 'O's
        auto valid = [&] (int r, int c) {
            return 0<=r && r<R && 0<=c && c<C;
        };

        auto visit = [&] (int r, int c) {
            if(board[r][c] == 'O') {
                board[r][c] = '.';
                bfs.push({r, c});
            }
        };

        for (int r=0; r<R; ++r) {
            visit(r, 0);
            visit(r, C-1);
        }
        for (int c=0; c<C; ++c) {
            visit(0, c);
            visit(R-1, c);
        }

        while (!bfs.empty()) {
            auto [r, c] = bfs.front(); bfs.pop();
            for (const auto [dr, dc] : DIRECTIONS) {
                const auto next_r = r+dr;
                const auto next_c = c+dc;
                if (valid(next_r, next_c)) {
                    visit(next_r, next_c);
                }
            }
        }

        for (int r=0; r<R; ++r) {
            for (int c=0; c<C; ++c) {
                if(board[r][c] == 'O') {
                    board[r][c] = 'X';
                }else if(board[r][c] == '.') {
                    board[r][c] = 'O';
                }
            }
        }
    }
};
