/*
You are given an m x n 2-D integer array matrix and an integer target.

Each row in matrix is sorted in non-decreasing order.
The first integer of every row is greater than the last integer of the previous row.
Return true if target exists within matrix or false otherwise.

Can you write a solution that runs in O(log(m * n)) time?

Example 1:



Input: matrix = [[1,2,4,8],[10,11,12,13],[14,20,30,40]], target = 10

Output: true
Example 2:



Input: matrix = [[1,2,4,8],[10,11,12,13],[14,20,30,40]], target = 15

Output: false
Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-10000 <= matrix[i][j], target <= 10000
*/
/*
RIGHT TOP corner is the key!!!!
    - if target > right top, then we can drop the whole row, because the row is sorted, and the first element of next row is bigger than the right top
    - if target < right top, then we can drop the whole column, because the column is sorted, and the right top is the smallest in that column
    - if target == right top, then we find it


*/ */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        const auto& R = matrix.size();
        const auto& C = matrix[0].size();
        int r=0;
        int c=C-1;
        while(r<R && c>=0){
            const auto& cur = matrix[r][c];
            if(cur == target) return true;
            if(cur < target) ++r;
            else --c;
        }

        return false;
    }
};
