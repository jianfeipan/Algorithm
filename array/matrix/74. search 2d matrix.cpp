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

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // binary search 
        const int rowCount = matrix.size();
        const int colCount = matrix[0].size();

        // the challeng is to find [row][col] given x
        // x = row*colCount + col
        // row = x/colCount;
        // col = x%colCount;

        int start = 0;
        int end = rowCount*colCount-1;
        while(start<=end){
            const int middle = (start+end)/2;
            const int mrow = middle/colCount;
            const int mcol = middle%colCount;
            const int middleValue = matrix[mrow][mcol];

            if(target > middleValue){
                start = middle+1;
            }else if(target < middleValue){
                end = middle-1;
            }else{
                return true;
            }
            
        }


        return false;
        

    }
};
