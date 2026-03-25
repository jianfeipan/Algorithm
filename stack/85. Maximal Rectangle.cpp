/*
85. Maximal Rectangle

Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example 1:
Input: matrix =
[
    ["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1


Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= rows, cols <= 200
matrix[i][j] is '0' or '1'.
*/

/*
idea:


The Strategy: Row-by-Row Histograms with Monotonic Stack
Imagine the matrix row by row. For each row, we calculate the height of "bars" consisting of consecutive 1s ending at that row.

Transform to Histograms: Maintain an array heights of size cols.
As you iterate through each row:If matrix[row][col] == '1', then heights[col] += 1.If matrix[row][col] == '0', then heights[col] = 0 (the bar is broken).

Apply Histogram Logic: After updating the heights for a row, treat that row as a histogram and find the largest rectangle it can form using a Monotonic Stack.
              c-1  c
    [1, 0,  1,  0,  0],
r-1 [1, 0,  1,  1,  1],
r   [1, 1,  1,  1,  1],
    [1, 0,  0,  1,  0]

you need a base line, to align the bars, then to find the max: row by row
find the consecutive 1s from that row: looking up

looking up: or histograms for each row:
              c-1  c
    [1, 0,  1,  0,  0],
r-1 [2, 0,  2,  1,  1],
r   [3, 1,  3,  2,  2],
    [4, 0,  0,  3,  0]

then row by row find the largest:
              0  1   2   3   4
for exmaple: [3, 0,  3,  2,  2]

a stack of min hightsL the minimum hight is the up limit of the rectangle


*/
class Solution {
public:

    int maximalRectangle(vector<vector<char>>& matrix) {
        const auto ROW = matrix.size();
        if (ROW == 0) return 0;
        const auto COL = matrix[0].size();

        vector<int> heights(COL+1, 0);


        /*
        get the histograme of columns
        idea:
            [1, 0,  1,  0,  0],
        r-1 [1, 0,  1,  1,  1],
        r   [1, 1,  1,  1,  1],
            [1, 0,  0,  1,  0]



        */
        int largest = 0;

        for (int r = 0; r < ROW; ++r){
            for (int c = 0; c < COL; ++c){
                if (matrix[r][c] == '1')
                    ++heights[c];
                else
                    heights[c] = 0;
            }
            // current row hights [3, 0,  3,  2,  2, 0 (have one more 0 to pop all previous hights and compute area)]
            // stack keeps the hights smaller than the current one, which means those rectangle can be extended here
            stack<int> monoton;
            int maxArea = 0;


            for (int c = 0; c <= COL; c++) {
                int currentHight = (c == COL) ? 0 : heights[c]; // COL index says: no more, let's stop here check all in the stack
                while (!monoton.empty() && currentHight < heights[monoton.top()]) {
                    // current hight is smaller,  the bigger ones in the stack should be pop and compute their area
                    int height = heights[monoton.top()];
                    monoton.pop();
                    int lastSmaller = monoton.empty() ? -1 : monoton.top();
                    int from = lastSmaller+1;
                    /*
                    after pop(), the top with index "from" is the first element from right to left smaller than height
                        -> from index `from` to index c-1, h>=height
                    */

                    int to = c-1;
                    int width = to - from + 1;
                    largest = max(largest, height * width);
                }
                monoton.push(c);
            }

        }
        return largest;
    }
};
