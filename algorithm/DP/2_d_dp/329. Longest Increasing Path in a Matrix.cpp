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

/*
[
[1,2,3],
[2,1,4],
[7,6,5]
]

*/
#include <array>
class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        {1,0},
        {-1,0},
        {0,-1},
        {0,1}
    }};

    int longestFrom(const vector<vector<int>>& matrix, 
                    int r, int c,
                    vector<vector<int>>& memory){
        const auto& R = matrix.size();
        const auto& C = matrix[0].size();
        
        auto& cache = memory[r][c];
        if(cache!=-1) return cache;

        int longest = 1;
        for(const auto& [dr, dc] : DIRECTIONS){
            auto newR = r+dr;
            auto newC = c+dc;

            if(newR<0 || newR>=R || newC<0 || newC>=C) continue;
            if(matrix[r][c] < matrix[newR][newC]) {
                longest = max(longest, 
                    1+longestFrom(matrix, newR, newC, memory)
                );
            }
        }
        return cache = longest;

    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        const auto& R = matrix.size();
        const auto& C = matrix[0].size();// 

        vector<vector<int>> memory(R, vector<int>(C, -1));
        int longest = 1;
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                longest = max(longest, longestFrom(matrix, r, c, memory));
            }
        }

        return longest;
    }
};

