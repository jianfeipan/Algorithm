/*
Given an array of intervals intervals where intervals[i] = [start_i, end_i], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note: Intervals are non-overlapping even if they have a common point. For example, [1, 3] and [2, 4] are overlapping, but [1, 2] and [2, 3] are non-overlapping.
--> exclusive
Example 1:

Input: intervals = [[1,2],[2,4],[1,4]]

Output: 1
Explanation: After [1,4] is removed, the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[2,4]]

Output: 0
*/


/*
fact:
    1 exclusive: (1, 2) (2, 3) -> no overlapping
    2 not sorted

idea:
    1. sort it by start, end
    2 detect overlapping
    3 try to remove -> this is tricky
        the question is minimum intervals to remove
        -> it's actualy maximum intervals no overlapping
        -> take 0 -> 
              |-> dont take 0-> 
        using a dfs
          



*/
class Solution_DP {
private:
    int maxNoOverlapping(const vector<vector<int>>& intervals, 
                        int current, int prev, vector<vector<int>>& memory){
        if(current == intervals.size()) return 0;

        auto& cache = memory[current][prev+1];
        if(cache != -1) return cache;

        // don't take current one
        int maxCount = maxNoOverlapping(intervals, current+1, prev, memory);
        if(-1 == prev
        || intervals[prev][1]<=intervals[current][0]){// no overlapping
            //current one can be taken
            maxCount = max(maxCount, 1+maxNoOverlapping(intervals, current+1, current, memory));
        }
        return cache = maxCount;
    }

public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> memory(intervals.size(), vector<int>(intervals.size(), -1));
        return intervals.size() - maxNoOverlapping(intervals, 0, -1, memory);
    }
};

class Solution_one_pass {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) 
    {
        if(intervals.empty()) return -1; // throw an exception
        
        int toBeDeleted = 0;
        sort(intervals.begin(), intervals.end());
        

        vector<int> currnetInterval = intervals[0];
        
        for(size_t i = 1; i < intervals.size(); ++i)
        {
            if(currnetInterval[1] >intervals[i][0])
            {//has overlapping
                ++toBeDeleted;
                if(currnetInterval[1] >= intervals[i][1])
                    currnetInterval = intervals[i];//keep the i interval: it ends earlier
                //remove the first one: currnetInterval stays
            }
            else{// no overlapping: we just move to next interval
                currnetInterval = intervals[i];
            }
        }
        return toBeDeleted;
    }
};

