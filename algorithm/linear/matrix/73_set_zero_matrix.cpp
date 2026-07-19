/*
Given an m x n matrix of integers matrix, 
if an element is 0, set its entire row and column to 0's.

You must update the matrix in-place.

Follow up: Could you solve it using O(1) space?

Example 1:



Input: matrix = [
  [0,1],
  [1,0]
]

Output: [
  [0,0],
  [0,0]
]
Example 2:

Input: matrix = [
  [1,2,3],
  [4,0,5],
  [6,7,8]
]

Output: [
  [1,0,3],
  [0,0,0],
  [6,0,8]
]
Constraints:

1 <= matrix.length, matrix[0].length <= 100
-2^31 <= matrix[i][j] <= (2^31) - 1
*/


/*
chalenge is O(1) space, wich mean in palce

however, once we put other 0, we lost the original 0 s


*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        const auto R = matrix.size(), C = matrix[0].size();
        // the key is to make use the first row: 
        // mark zeros when that col is zero on the zero row, 
        // set the matrix[0] to zero or not in the end when we set all other lines
        bool row0ShouldBeSetToZero = false;
        for (int c = 0; c < C; c++) {
            if(matrix[0][c] == 0){
                row0ShouldBeSetToZero = true;
            }
        }
        
        bool col0ShouldBeSetToZero = false;
        for (int r = 0; r < R; r++) {
            if(matrix[r][0] == 0){
                col0ShouldBeSetToZero = true;
            }
        }


        for (int r = 1; r < R; r++) {
            for (int c = 1; c < C; c++) {
                if (matrix[r][c] == 0) {
                    matrix[0][c] = 0;// mark the col on row 0
                    matrix[r][0] = 0;// mark the row on col 0
                }
            }
        }


        //set zeros by chekcing row0 and col0
        for (int r = 1; r < R; r++) {
            for (int c = 1; c < C; c++) {
                if (matrix[0][c] == 0 || matrix[r][0] == 0) {
                    matrix[r][c] = 0;
                }
            }
        }

        if( row0ShouldBeSetToZero )
            for (int c = 0; c < C; c++) {
                matrix[0][c] = 0;
            }
        
        if( col0ShouldBeSetToZero )
            for (int r = 0; r < R; r++) {
                matrix[r][0] = 0;
            }

    }
};
