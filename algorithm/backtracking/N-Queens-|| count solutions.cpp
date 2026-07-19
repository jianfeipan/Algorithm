class Solution {
private:
    int safe(const vector<vector<int>>& board, int r, int c){
        const int n = board.size();

        // check first r rows of column = c
        for(int i=0; i<r; ++i) if(board[i][c] == 1) return false;

        // check first c columns of row = r
        for(int i=0; i<c; ++i) if(board[r][i] == 1) return false;

        // check right up
        for(int i=0; c+i<n && r-i>=0; ++i) if(board[r-i][c+i] == 1) return false;

        // check left up
        for(int i=0; c-i>=0 && r-i>=0; ++i) if(board[r-i][c-i] == 1) return false;

        return true;
        
     }

    int placeOnRow(int r, vector<vector<int>>& board){
        const int n = board.size();

        if(r == n) return 1;// if r reaches n, we have one solution

        int solutions = 0;
        for(int c = 0; c<n; ++c){
            if(safe(board, r, c)){
                board[r][c] = 1;
                solutions+=placeOnRow(r+1, board);
                board[r][c] = 0; // backtracing
            }
        }

        return solutions;
    }
public:
    int totalNQueens(int n) {
        vector<vector<int>> board(n, vector<int>(n));
        // put one place in the current row, then go to next row
        return placeOnRow(0, board);
    }
};
