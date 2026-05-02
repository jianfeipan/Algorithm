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

