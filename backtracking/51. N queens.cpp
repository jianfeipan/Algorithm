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

*/
class Solution {
private:
    bool isSafe(const vector<string>& board, int r, int c){
        const int n = board.size();

        for(int i = 0; i<n; ++i)
            if(board[i][c]=='Q') return false; // check this col (row is safe) and below row is safe

        for(int i=r-1, j=c-1; i>=0 && j>=0; --i, --j) // check only left up!!!!
            if(board[i][j]=='Q') return false;

        for(int i=r-1, j=c+1; i>=0 && j<n; --i, ++j) // check only right up!!!!
            if(board[i][j]=='Q') return false;

        return true;
    }

    void putQueens(vector<string>& board, int r, vector<vector<string>>& res){
        if(r == board.size()){
            res.push_back(board);
            return;
        }
        // let's place queue on the current row
        for(int c=0; c<board[r].size(); ++c){
            if(isSafe(board, r, c)){
                board[r][c] = 'Q';  
                putQueens(board, r+1, res);
                board[r][c] = '.';  // bakctracing
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));

        vector<vector<string>> res;
        putQueens(board, 0, res);
        return res;
    }
};


