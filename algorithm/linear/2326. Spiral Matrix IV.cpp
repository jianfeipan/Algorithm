/*

You are given two integers m and n, which represent the dimensions of a matrix.

You are also given the head of a linked list of integers.

Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.

Return the generated matrix.

 

Example 1:
Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
Explanation: The diagram above shows how the values are printed in the matrix.
Note that the remaining spaces in the matrix are filled with -1.
Example 2:
Input: m = 1, n = 4, head = [0,1,2]
Output: [[0,1,2,-1]]
Explanation: The diagram above shows how the values are printed from left to right in the matrix.
The last space in the matrix is set to -1.


*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {

private:

    void turn(array<int, 2> & direction)
    {
                    //Turn direction
            /*
            0,1     ->  1,0
            1,0    ->  0,-1
            0,-1    ->  -1, 0
            -1,0    -> 0,1
            
            */
            if(direction[0] == 0)
            {
                direction[0] = direction[1];
                direction[1] = 0;
            }
            else
            {
                direction[1] = -1*direction[0];
                direction[0]=0;
            }
    }

    bool moveNext(int & row, int & col, array<int, 2> & direction, const vector<vector<int>> &res)
    {
        int nextRow = row + direction[0];
        int nextCol = col + direction[1];

        //cout<<"next : ("<<nextRow<<","<<nextCol<<") ";


        if(nextRow>=0 && nextRow<res.size() && nextCol>=0 && nextCol<res[nextRow].size() && res[nextRow][nextCol]==-1)
        {
            //next is valide
            row = nextRow;
            col = nextCol;
            //cout<<"("<<row<<","<<col<<") ";
            return true;
        }
        else
        {
            for(int i = 0; i<3; ++i)//only turn 3 times to avoid infinite loop
            {
                turn(direction);
                int _nextRow = row + direction[0];
                int _nextCol = col + direction[1];
                if(_nextRow>=0 && _nextRow<res.size() && _nextCol>=0 && _nextCol<res[_nextRow].size() && res[_nextRow][_nextCol]==-1)
                {
                    //next is valide
                    row = _nextRow;
                    col = _nextCol;
                    return true;
                }
            }
            
            //return moveNext(raw, col, direction, res); recursive may have infinite loop problem

            return false;

        }
    }

public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> res(m, vector<int>(n, -1));
        int row = 0;
        int col = -1;
        array<int, 2> direction = {0, 1}; 

        while(head && moveNext(row, col, direction, res))
        {
            res[row][col]=head->val;
            head=head->next;
        }

        return res;

    }
};
