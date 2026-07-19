
/*
861. Score After Flipping Matrix
Medium
1.5K
176
Companies
You are given an m x n binary matrix grid.

A move consists of choosing any row or column and toggling each value in that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).

Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score after making any number of moves (including zero moves).

 

Example 1:


Input: grid = [
    [0,0,1,1],
    [1,0,1,0],
    [1,1,0,0]
]
  ->[1,1,0,0],
    [1,0,1,0],
    [1,1,0,0]

         |   
         v                   
    [1,1,1,0],
    [1,0,0,0],
    [1,1,1,0]


           |   
           v                   
    [1,1,1,1],
    [1,0,0,1],
    [1,1,1,1]



Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
Example 2:

Input: grid = [[0]]
Output: 1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 20
grid[i][j] is either 0 or 1.
*/
class Solution {

    /*
    fact:
        any moves
        score is binary and the computation is idependdent
    idea:
        compute score 
        max --> we need to check what move means to the max:    
            row move: if more 1 on the left, do it
            col move: if more 1, do it
    */

private:
    int get_score(const vector<int>& nums){
        int val = 0;
        for(auto num:nums){
            val*=2;
            val+=num;
        }
        //cout<<val<<endl;
        return val;
    }

public:
    int matrixScore(vector<vector<int>>& grid) {
        //greedy:
        //row move: make first digit 1

        for(auto & line:grid){
            if(line[0]==0){//flip
                for(auto& digit:line){
                    // if(digit==0){
                    //     digit=1;
                    // }else{
                    //     digit=0;
                    // }
                    digit = 1 - digit;

                }
            }
        }

        //all first digit are 1 now
        //col
        for(int col=1; col<grid[0].size(); ++col){
            int count = 0;
            for(auto & line:grid){
                if(line[col]==1){
                    ++count;
                }
            }

            if(count<=grid.size()/2){
                for(auto & line:grid){
                    // if(line[col]==1) line[col]=0;
                    // else line[col]=1;
                    line[col] = 1 - line[col];
                }
            }
        }
        int score=0;
        for(const auto & line:grid){
            score+=get_score(line);
        }

        return score;
    }
};
