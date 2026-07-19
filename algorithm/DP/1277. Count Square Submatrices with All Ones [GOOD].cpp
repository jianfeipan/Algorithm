/*
1277. Count Square Submatrices with All Ones
Medium
4.7K
75
Companies
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

 

Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.
Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.
 

Constraints:

1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1

*/

class Solution {
    /*
    fact:
        from side 1 to side min(m, n)

    idea:
        manually, we start from top left to bottom right, take one as top left square then count from side 1 to side x (x depends on where we are)

    improvement:

        --> top down method dp is making slower: is_square_dp


        the right way is:  dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) ??? why --> 
        
        1, 1
        1, 1

        
        dp[i][j] represent the number of squares added by adding this position, it depends on dp[i-1][j], dp[i][j-1], dp[i-1][j-1], if any of them is 0, this position add only one, so we could have :
        
    int countSquares(vector<vector<int>>& matrix) {
        int counter = 0;

        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    continue;
                }
                matrix[i][j] = min(min(matrix[i-1][j-1], matrix[i][j-1]), matrix[i-1][j]) + 1;
            }
        }
        
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                counter += matrix[i][j];
            }
        }

        return counter;
    }


        
        

    */
private:

    int is_square(const vector<vector<int>>& matrix, int i, int j, int side){
         //what should we veryfy: not every element, just new elements
            const int check_row = i + side -1;
            bool all_one = true;
            for(int col = j; col<j+side; ++col){
                if(matrix[check_row][col]!=1)
                {
                    return false;
                }
            }

            const int check_col = j+side-1;
            for(int row = i; row<i+side; ++row){
                if(matrix[row][check_col]!=1)
                {
                    return false;
                }
            }

            return true;
    }

    int countSquaresFrom(const vector<vector<int>>& matrix, int i, int j){
        int count = 1;//it self count  1
        const int max_side = std::min(matrix.size() - i, matrix[0].size()-j);
        for(int side = 2; side <= max_side; ++side){
            if(is_square(matrix, i, j, side)){
                ++count;
            }else{
                break;
            }
        }

        return count;
    }


    bool is_square_dp(const vector<vector<int>>& matrix, int i, int j, int side){
        if(matrix[i][j] != 1) return false;
        auto & cached = cache[i][j][side];
        if(cached!=0) return cached==1;
        
        if(side == 1){
            cached = 1;
            return true;
        }

        if(is_square_dp(matrix, i+1, j+1, side-1) && is_square_dp(matrix, i+1, j, side-1) && is_square_dp(matrix, i, j+1, side-1)){
            cached = 1;

            return true;
        }

        cached = -1;
        return false;
    }


    int countSquaresFrom_dp(const vector<vector<int>>& matrix, int i, int j){
        int count = 1;//it self count  1
        const int max_side = std::min(matrix.size() - i, matrix[0].size()-j);
        for(int side = 2; side <= max_side; ++side){
            if(is_square_dp(matrix, i, j, side)){
                ++count;
            }else{
                break;
            }
        }

        return count;
    }
private:
    map<int, map<int, map<int, int>>> cache;
public:
    int countSquares(vector<vector<int>>& matrix) {
        int count = 0;
        for(int i = 0; i<matrix.size(); ++i){
            for(int j = 0; j<matrix[i].size();++j){
                if(matrix[i][j]==1){
                    count+=countSquaresFrom_dp(matrix, i, j);
                }
            }
        }
        return count;
    }
};
