    /*
    1637. Widest Vertical Area Between Two Points Containing No Points
Medium
304
695
Companies
Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.

A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.

Note that points on the edge of a vertical area are not considered included in the area.

 

Example 1:
Input: points = [[8,7],[9,9],[7,4],[9,7]]
Output: 1
Explanation: Both the red and the blue area are optimal.
    */


class Solution {
/*
fact:
    1 axle y makes NO SENSE!

idea: 
    focus on x values, find the biggest diff between beighbors-> sort



*/

public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        if(points.empty()) return 0;

        set<int> xValues; //Any way, we need a new container, why not using a sorted container instead fof push into a vector than sort it
        for(const auto & point : points)
        {
            xValues.insert(point[0]);
        }

        int maxDiff = 0;
        auto it = xValues.cbegin();
        int lastNumber = *it;
        ++it;
        for(; it!=xValues.cend(); ++it)
        {
            maxDiff = std::max(maxDiff, *it - lastNumber);

            lastNumber = *it;
        }   

        return maxDiff;
    }
};
