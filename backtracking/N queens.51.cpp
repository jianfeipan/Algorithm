/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard so that no two queens can attack each other.

A queen in a chessboard can attack horizontally, vertically, and diagonally.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a unique board layout where the queen pieces are placed. 'Q' indicates a queen and '.' indicates an empty space.

You may return the answer in any order.

Example 1:



Input: n = 4

Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There are two different solutions to the 4-queens puzzle.

Example 2:

Input: n = 1

Output: [["Q"]]
Constraints:

1 <= n <= 8

*/class Solution {
private:
    bool safe(int r, int c, int n, const vector<string> & current){
        // we are placing from top-left to right bottom
        // we only need to check up same col, left same row, left-up diagonal, right-up diagonal
        
        // look up
        for(int row = 0; row < r; ++row) if(current[row][c] == 'Q') return false;

        //left same row, : left same row is not possile , we place only one each row

        // left-up diagonal 
        for(int i = 0; r - i >= 0 && c - i >= 0; ++i) if(current[r-i][c-i] == 'Q') return false;
        // right-up diagonal
        for(int i = 0; r - i >= 0 && c + i < n; ++i) if(current[r-i][c+i] == 'Q') return false;
        
        return true;
    }

    void put_queen_on_row(int r, int n,
                            vector<string> & current, 
                            vector<vector<string>> & res){
        if(r == n) { res.push_back(current); return; }
        
        for(int c = 0; c < n; ++c){
            if(safe(r, c, n, current)){
                current[r][c] = 'Q';
                put_queen_on_row(r+1, n, current, res);
                current[r][c] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> current(n, string(n, '.'));
        put_queen_on_row(0, n, current, res);
        return res;
    }
};
