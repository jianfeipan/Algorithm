/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.


Input: matrix = [
    [1, 4, 7, 11,15],
    [2, 5, 8, 12,19],
    [3, 6, 9, 16,22],
    [10,13,14,17,24],
    [18,21,23,26,30]], target = 5
Output: true

*/

/*
idea:
    the feature of the matrix: m[r][c] < m[r+1][c], <m[r][c+1]

    do binary search on each line: O(R*logC)

    we need kind of if < move to one direction, if > move to another direction
    search from top-right!!!

    here when target < current: move left,
              target > current: move down
    
    O(m+n)
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;

        const auto R = matrix.size();
        const auto C = matrix[0].size();
        int r = 0; // top
        int c = C-1; // right
        while( r>=0 && r<R 
            && c>=0 && c<C){
            const auto& current = matrix[r][c];
            if( current == target) return true;
            if(current < target) ++r; // go down
            else --c; // go left
        }
        return false;
    }
};
