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
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;
        stack<int> increasing;
        
        for(int i=0; i<=n; ++i){
            while(!increasing.empty() 
                && (heights[increasing.top()] >= heights[i]
                    || i == n)){
                auto lastBigger = heights[increasing.top()];
                increasing.pop();
                // witdh to previous smaller
                auto width = increasing.empty() ? i : i - increasing.top() - 1;
                maxArea = max(maxArea, width*lastBigger);
            }
            increasing.push(i);
        }
       


        return maxArea;

    }
};
