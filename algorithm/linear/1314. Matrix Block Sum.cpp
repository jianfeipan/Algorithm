
/*
1314. Matrix Block Sum
Medium
2.3K
347
Companies
Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:

i - k <= r <= i + k,
j - k <= c <= j + k, and
(r, c) is a valid position in the matrix.
 

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]
Example 2:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n, k <= 100
1 <= mat[i][j] <= 100
*/
class Solution {
/*
fact:
idea:
    sum matrix to avoid repeated computations

*/
 int m, n;
public:
    int block_sum(int row, int col, vector<vector<int>>& prefix_sum, int k) {
        // relevant points are
        // bottom corner            -> row + k,     col + k
        // top corner               -> row - k,     col - k;
        // pre up corner            -> row - k - 1, col - k - 1;
        // right up corner          -> row - k - 1, col + k
        // left down corner         -> row + k,     col - k - 1
        // sum 
        // value(bottom corner) - value(right up) - value(left down) + value(pre up corner);
        int bot_corner_row = min(row + k, m - 1);
        int bot_corner_col = min(col + k, n - 1);
        // Base block
        int res = prefix_sum[bot_corner_row][bot_corner_col];
        // Block 1 - Upper block
        if ((row - k - 1) >= 0) {
            int right_up_corner_col = min(col + k, n - 1);
            res -= prefix_sum[row - k - 1][right_up_corner_col];
        }
        // Block 2 - Left block
        if ((col - k - 1) >= 0) {
            int left_down_corner_row = min(row + k, m - 1);
            res -= prefix_sum[left_down_corner_row][col - k - 1];
        } 
        // Block 3 - upper left block
        // Add if both Block 1 & 2 reduced its sum
        if (((row - k - 1) >= 0) && ((col - k - 1) >= 0)) {
            res += prefix_sum[row - k - 1][col - k - 1];
        }
        return res;
    }
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        m = mat.size();
        n = mat[0].size();
        vector<vector<int>> prefix_sum(m, vector<int>(n, 0));
        vector<vector<int>> result(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; ++i) {
            int row_sum = 0;
            for (int j = 0; j < n; ++j) {
                // Prefix sum is accumulated sum of row element + upper prefix sum cell
                row_sum += mat[i][j];
                prefix_sum[i][j] = row_sum;
                if (i > 0) {
                    prefix_sum[i][j] += prefix_sum[i - 1][j];
                }
            }
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = block_sum(i, j, prefix_sum, k);
            }
        }
        return result;
    }
};
