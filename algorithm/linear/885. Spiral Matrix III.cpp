/*
885. Spiral Matrix III
Medium
Topics
Companies
You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.

You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.

Return an array of coordinates representing the positions of the grid in the order you visited them.

 

Example 1:


Input: rows = 1, cols = 4, rStart = 0, cStart = 0
Output: [[0,0],[0,1],[0,2],[0,3]]
Example 2:


Input: rows = 5, cols = 6, rStart = 1, cStart = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
 

Constraints:

1 <= rows, cols <= 100
0 <= rStart < rows
0 <= cStart < cols

*/


class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> res;res.reserve(rows*cols);
        
        static const vector<vector<int>> directions = {
            {0, 1}, //right
            {1, 0}, //down
            {0, -1}, //left
            {-1, 0}//up
        };
        const int totalSteps= rows*cols;
        int r = rStart;
        int c = cStart;

        //spiral manipulation!!! 
        int currentRepeatNum = 1;
        int repeated= 0;
        int currentDirection = 0;

        int step = 1;
        // just go with spiral, only validated position will be put a step number
        for(int i = 0; step<=totalSteps; ++i){

            if(r>=0 && r<rows && c>=0 && c<cols){
                res.push_back({r,c});
                ++step;
            }
            //std::cout<<r<<","<<c<<std::endl;

            const auto & direction = directions[currentDirection];
            r = direction[0]+r;
            c = direction[1]+c;

            ++repeated;
            if(currentRepeatNum == repeated){
                repeated = 0;

                if(currentDirection == 1 || currentDirection == 3)
                {
                    ++currentRepeatNum;
                }
                currentDirection=(currentDirection+1)%4;
            }
        }

        return res;
        
    }
};
