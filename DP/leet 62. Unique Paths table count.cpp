/*
Unique Paths
Medium
Topics
Company Tags
Hints
There is an m x n grid where you are allowed to move either down or to the right at any point in time.

Given the two integers m and n, return the number of possible unique paths that can be taken from the top-left corner of the grid (grid[0][0]) to the bottom-right corner (grid[m - 1][n - 1]).

You may assume the output will fit in a 32-bit integer.

Example 1:



Input: m = 3, n = 6

Output: 21
Example 2:

Input: m = 3, n = 3

Output: 6
Constraints:

1 <= m, n <= 100
*/
class Solution {

/*
idea:
    DP problem: 
        path(m, n) = path(m-1, n) + path(m, n-1)
        O(2^(m+n))

        improvement is a cache, n*m vector to have the path number cached
        O(m*n)
*/
private:
    int _paths(int m, int n, vector<vector<int>>& cache){
        if(m==0 && n==0){
            return 1;
        }
        if(m<0 || n<0){
            return 0;
        }
        if(cache[m][n]!=-1){
            return cache[m][n];
        }
        return cache[m][n]=(_paths(m-1, n, cache) + _paths(m, n-1, cache));
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> cache(m+1, vector<int>(n+1, -1));
        return _paths(m-1, n-1, cache);
    }
};
