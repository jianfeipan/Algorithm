/*
Spiral Matrix
Medium
Topics
Company Tags
Hints
Given an m x n matrix of integers matrix, return a list of all elements within the matrix in spiral order.

Example 1:



Input: matrix = [[1,2],[3,4]]

Output: [1,2,4,3]
Example 2:



Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]

Output: [1,2,3,6,9,8,7,4,5]
Example 3:

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]

Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/


/*
idea:
    start from 0, 0 
    direction swich oder: {0, 1} {1, 0} {0, -1} {-1, 0} (R, D, L, U)
    every time go straight, when it's boundry, or visited, turn direction. 
    if no more unvisited after turn direction, finished
*/
#include<array>
constexpr array<array<int, 2>, 4> DIRECTIONS{{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
}};
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        const auto R = matrix.size();
        if(R==0) return {};
        const auto C = matrix[0].size();
        int currentDir = 0;
        int r = 0;
        int c = 0;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        const auto N = R*C;
        vector<int> order; order.reserve(N);

        while(order.size() < N){
            order.push_back(matrix[r][c]); visited[r][c]=true;

            int newR = r+ DIRECTIONS[currentDir][0];
            int newC = c+ DIRECTIONS[currentDir][1];
            if(newR<0 || newR>=R || newC<0 || newC>=C || visited[newR][newC]){
                currentDir = (currentDir+1)%4;
            }
            // after turining once, we just go that direction, if still visited , we finished
            r += DIRECTIONS[currentDir][0];
            c += DIRECTIONS[currentDir][1];
        }

        return order;
    }
};
