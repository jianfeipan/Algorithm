/*

419. Battleships in a Board
Medium
2.1K
919
Companies
Given an m x n matrix board where each cell is a battleship 'X' or empty '.', return the number of the battleships on board.

Battleships can only be placed horizontally or vertically on board. In other words, they can only be made of the shape 1 x k (1 row, k columns) or k x 1 (k rows, 1 column), where k can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e., there are no adjacent battleships).

 

Example 1:

Input: board = [
    ["X",".",".","X"],
    [".",".",".","X"],
    [".",".",".","X"]]
Output: 2
Example 2:

Input: board = [["."]]
Output: 0

*/

class Solution {

    /*
    fact:
        only horizontal or vertical
    idea:
        scan and count, mark the adjacents as counted

    */
public:
    int countBattleships(vector<vector<char>>& board) {
        int count = 0;

        for(int row = 0; row < board.size(); ++row)
        {
            for(int col = 0; col < board[row].size(); ++col)
            {
                if(board[row][col] == 'X')
                {
                    count++;
                    
                    board[row][col] = 'O';
                    //we count from left, top, so the left only can be on right or down

                    if(col+1< board[row].size() && board[row][col+1] == 'X')
                    {
                        for(int i = col+1; i<board[row].size();++i)
                        {
                            if(board[row][i] == 'X') board[row][i] = 'O';
                            else break;
                        }
                    }
                    else if(row+1< board.size() && board[row+1][col] == 'X')
                    {
                        for(int i = row+1; i<board.size();++i)
                        {
                            if(board[i][col] == 'X') board[i][col] = 'O';
                            else break;
                        }
                    }

                }
            }
        }

        return count;
    }
};
