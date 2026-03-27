/*
Given a square n x n matrix of integers matrix, rotate it by 90 degrees clockwise.

You must rotate the matrix in-place. Do not allocate another 2D matrix and do the rotation.

1 2       3 1
3 4  ->   4 2
 rotation seems complex
 but we can do transpose (nxn) then left right fold
 1 2
 3 4  -> transpose 

 1 3
 2 4 -> mirror left-right

 3 1
 4 2

*/

class Solution {
private: 
    void transpose(vector<vector<int>>& matrix){
        const int R = matrix.size();
        const int C = matrix[0].size();
        for(int r = 0; r<R; ++r){
            for(int c = r+1; c<C; ++c){
                auto temp = matrix[r][c];
                matrix[r][c] = matrix[c][r];
                matrix[c][r] = temp;
            }
        }
    }

    void leftRightMirror(vector<vector<int>>& matrix){
        for(auto& row : matrix){
            const auto n = row.size();
            const auto m = n / 2;
            // 0 1 2   m = 3/2 = 1
            // 0 1 2 3  m = 4/2 = 2
            for(int i=0; i<m; ++i){
                int temp = row[i];
                row[i] = row[n - i -1];
                row[n - i -1] = temp;
            }
        }
    }
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size() <= 0) return;

        transpose(matrix);
        leftRightMirror(matrix);
    }
};
