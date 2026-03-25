/*
329. Longest Increasing Path in a Matrix


You are given a 2-D grid of integers matrix, where each integer is greater than or equal to 0.

Return the length of the longest strictly increasing path within matrix.

From each cell within the path, you can move either horizontally or vertically. You may not move diagonally.
Input: matrix = [[5,5,3],[2,3,6],[1,1,1]]

Output: 4
Explanation: The longest increasing path is [1, 2, 3, 6] or [1, 2, 3, 5].

Example 2:
Input: matrix = [[1,2,3],[2,1,4],[7,6,5]]

Output: 7
*/


/*
idea:
    start from all point, 
    dfs discover the path: recursive call on the greater neighbor
    we need a matrix for visited, 
    back trace after recursive
    pass a reference to put the longest path

O(m*n) every cell we only compute once.
space: O(m*n)
*/

#include<array>

constexpr array<array<int, 2>, 4> DIRECTIONS{{
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
}};

class Solution {
private:
    int dfs(const vector<vector<int>>& matrix, 
             int row, int col, vector<vector<int>>& memory){

        auto& cache = memory[row][col];
        if(cache != -1) return cache;
        const auto& ROW = matrix.size();
        const auto& COL = matrix[0].size();
        
        int maxLen = 1;
        for(const auto& [dr, dc] : DIRECTIONS){
            int r = row+dr;
            int c = col+dc;
            if( r>=0 && r<ROW
                && c>=0 && c<COL
                && matrix[row][col] < matrix[r][c]){
                maxLen = max(maxLen, 
                    1+ dfs(matrix, r, c, memory));
            }
        }
        return cache = maxLen;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        const auto& ROW = matrix.size();
        if(ROW == 0) return 0;
        const auto& COL = matrix[0].size();
        if(COL == 0) return 0;

        vector<vector<int>> memory(ROW, vector<int>(COL, -1));
        //noneed of visited: we are alwasy going up
        int maxLen = 0;
        for(int r=0; r<ROW; ++r){
            for(int c=0; c<COL; ++c){
                maxLen = max(maxLen, dfs(matrix, r, c, memory));
            }
        }

        return maxLen;
    }
};
