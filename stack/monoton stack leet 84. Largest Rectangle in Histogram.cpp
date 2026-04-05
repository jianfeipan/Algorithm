/*
You are given an array of integers heights where heights[i] represents the height of a bar. The width of each bar is 1.

Return the area of the largest rectangle that can be formed among the bars.

Note: This chart is known as a histogram.

Example 1:

Input: heights = [7,1,7,2,2,4]

Output: 8
Example 2:

Input: heights = [1,3,7]

Output: 7
*/
/*
facts:
    1. area = maxH * width
idea:
    BF: all rectangles: O(N^3)
    for every bar: 
        take it's hight
        try to extend to left, and try to extend to right
         0 1 2 3 4 5
        [7,1,7,2,2,4]
        0: 7
        1: 0-5 6
        2: 7
        3: 2-5 8
        ...
        O(n^2)
    stack: keep track the smaller heights increasing in stack
            at index i
           stack top > current[i],   pop
           previous element (stop top)'s right extend will stop at i-1
           left extend will stop at prev in the stack (top after pop)
    

*/

class Solution {


/*                0 1 2 3 4 5
Input: heights = [7,1,7,2,2,4]

area = minH * (r-l+1)
r   minH area
0    7     7
1    1     2
2    1     3 < 7

area depends: current height, and how far this height can extend to left
                                  -> monoton stack: keep track heigher in front (decreasing)

r   cur   area        stack
0    7     7           7
1    1     2           7>1 : the last element of 7 cannot extend to right, so the max for this 7, is on left, and we will pop  them, becasue the current one will make those heights not usable by pillars on the right of current
2    7     ?           1,7
3    2     7           1,2
...                  1  3  4  5
5    4              [1, 2, 2, 4]
6*               max(4*(6-4-1) ,  2*(6-3-1), 2*(6-1-1))
* we need the index in the stack to calculate the width

*/
public:
    int largestRectangleArea(vector<int>& heights) {

        int largest=0;
        heights.push_back(0);// for the last one to be out of stack
        
        stack<int> increasing;
        for(int r=0; r<heights.size(); ++r){
            while(!increasing.empty() && heights[increasing.top()]>heights[r]){
                // the top reaches the end to r, it can only extend to left
                // to left, it stops next top, next top is smaller than this top
                auto height = heights[increasing.top()];
                increasing.pop();
                auto leftBoundry = increasing.empty() ? -1 : increasing.top();
                auto width = r - 1 - leftBoundry;
                largest = max(largest, height*width);
            }
            increasing.push(r);
        }
        return largest;

    }
};

