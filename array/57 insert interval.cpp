/*

You are given an array of non-overlapping intervals intervals where intervals[i] = [start_i, end_i] represents the start and the end time of the ith interval. intervals is initially sorted in ascending order by start_i.

You are given another interval newInterval = [start, end].

Insert newInterval into intervals such that intervals is still sorted in ascending order by start_i and also intervals still does not have any overlapping intervals. You may merge the overlapping intervals if needed.

Return intervals after adding newInterval.

Note: Intervals are non-overlapping if they have no common point. For example, [1,2] and [3,4] are non-overlapping, but [1,2] and [2,3] are overlapping.

Example 1:

Input: intervals = [[1,3],[4,6]], newInterval = [2,5]

Output: [[1,6]]
Example 2:

Input: intervals = [[1,2],[3,5],[9,10]], newInterval = [6,7]

Output: [[1,2],[3,5],[6,7],[9,10]]

*/

/*
facts:  
    - ordered by start
    - no overlappings

idea:
    - find the start order to insert: [ [ ..  [  {new  [   
    - different cases:
        [] {} [] no overlapping
        
        [ {} ] []  include by previous
        [ {] } []  merge with previous

        [] [{}]   include by next
        [] { [ } ]  merge with next

        [  {] [}   ]  merge prev and next

*/

class Solution {

public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) return {newInterval};

        int n = intervals.size();
        int target = newInterval[0];
        int l = 0, r = n - 1;
        while(l<=r){
            int m = (l+r)/2;
            if(intervals[m][0] < target) l=m+1;
            else r=m-1; 
        }
        
        // l is the lower_bound: first element >= target
        
        // just place it in the l place, so the first bigger one will be l+1
        intervals.insert(intervals.begin() + l, newInterval);
        
        vector<vector<int>> res;
        for (const auto& interval : intervals) {
            if (res.empty() || res.back()[1] < interval[0]) {
                res.push_back(interval);// no overlapping
            } else {
                // when overlapping, just extend the tail
                res.back()[1] = max(res.back()[1], interval[1]);
            }
        }

        return res;

    }
};
