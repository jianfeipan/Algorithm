/*
221. Maximal Square

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

 

Example 1:


Input: matrix = [
    ["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]]
Output: 4
Example 2:


Input: matrix = [["0","1"],
                 ["1","0"]]
Output: 1
Example 3:

Input: matrix = [["0"]]
Output: 0
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.
*/

/*
scan all 1s, and extend squer from that one to right bottom, 
O(n^2)

*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        const auto& R = matrix.size();
        const auto& C = matrix[0].size();
        if(C == 0) return 0;
/*
                c-1   c
        r-1     1     <
        r       ^

              c
            1 1 1
         r  0 1 1
            1 1 1 
*/
        // actually you don't need to know the up or left consecutive, after all we are looking at the min of them
        // and the min of them is actually the dp itself: 
        // dp[i][j] mins using i as right bottom point, what is the largest square size?
        // !!! using R+1 and C+1 to have a all zero edge on left and top to avoid r-1 anc c-1 out of boundry

        vector<vector<int>> dp(R+1, vector<int>(C+1, 0));
        /*
        
        
              c
          0 0 0 0   
          0 1 1 1
        r 0 0 1 1
          0 1 1 1 
        */
        int largest = 0;
        for(int r = 1; r <= R; ++r){
            for(int c = 1; c <= C; ++c){
                if(matrix[r-1][c-1] == '1'){
                    dp[r][c] = min({
                                    dp[r-1][c],
                                    dp[r][c-1],
                                    dp[r-1][c-1]
                                  })+1;
                    largest=max(largest, dp[r][c]);
                }
            }
        }
        
        return largest*largest;
    }
};
