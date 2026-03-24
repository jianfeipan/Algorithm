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
            on position [r,c], the square's size depends on: 
                1. how large is the square on r-1, c-1: for exmaple: 1 (if everything is good, r, c will be 1+1)
                2. how many consecutive ones look left: 1
                3. how many consecutive ones look up: 2
            so the square can reach: min(1+1, 1, 2)=1

            on position [r+1, c+1]:
                1. how large is the square on r-1, c-1: for exmaple: 1 (if everything is good, r, c will be 1+1)
                2. how many consecutive ones look left: 3
                3. how many consecutive ones look up: 3
            so the square can reach min(1+1, 3, 3) = 2 so the arear is 2*2 = 4
            

*/
        // consecutive ones look left and look up
        // !!! using R+1 and C+1 to have a all zero edge on left and top to avoid r-1 anc c-1 out of boundry
        vector<vector<int>> onesLeft(R+1, vector<int>(C+1, 0));
        vector<vector<int>> onesUp(R+1, vector<int>(C+1, 0));

        int maxArea = 0;
        for(int r = 1; r <= R; ++r){
            for(int c = 1; c <= C; ++c){
                if(matrix[r-1][c-1] == '1'){
                   onesLeft[r][c] = onesLeft[r][c-1] + 1;
                   onesUp[r][c] = onesUp[r-1][c] +1;
                }
            }
        }
        
        vector<vector<int>> maxSize(R+1, vector<int>(C+1, 0));
        int largest = 0;

        for(int r = 1; r <= R; ++r){
            for(int c = 1; c <= C; ++c){
                if(matrix[r-1][c-1] == '1'){
                    maxSize[r][c] = min({maxSize[r-1][c-1]+1, onesLeft[r][c], onesUp[r][c]});
                    largest=max(largest, maxSize[r][c]);
                }
            }
        }
        return largest*largest;
    }
};
