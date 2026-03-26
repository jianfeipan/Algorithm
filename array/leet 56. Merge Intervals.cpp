/*
Merge Intervals

Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

You may return the answer in any order.

Note: Intervals are non-overlapping if they have no common point. For example, [1, 2] and [3, 4] are non-overlapping, but [1, 2] and [2, 3] are overlapping.

Example 1:

Input: intervals = [[1,3],[1,5],[6,7]]

Output: [[1,5],[6,7]]
Example 2:

Input: intervals = [[1,2],[2,3]]

Output: [[1,3]]


*/


/*
sort intervals by start,
then start to add from first one: 
    if empty, just add
    if not empty: check if the current tail's end overlap with next interval to be add
    -> push or merge(merge means end=max(end, newNode's end))

*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged; 
        for(const auto& interval : intervals){
            if(merged.empty() || merged.back()[1] < interval[0]){ // first or no overlapping
                merged.push_back(interval);
            }else{
                merged.back()[1] = max(merged.back()[1], interval[1]); // extend the tail's end
            }
        }

        return merged;
    }
};
