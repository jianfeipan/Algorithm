/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

/*
描述
给出若干闭合区间，合并所有重叠的部分。

样例
样例1:

输入: [(1,3)]
输出: [(1,3)]
样例 2:

输入:  [(1,3),(2,6),(8,10),(15,18)]
输出: [(1,6),(8,10),(15,18)]
挑战
O(n log n) 的时间和 O(1) 的额外空间。

[(2,3),(2,2),(3,3),(1,3),(5,7),(2,2),(4,6)]
[(2,3),(2,2),(3,3),(5,7),(2,2),(4,6),(0,0)]

*/

class Solution {
public:
    /**
     * @param intervals: interval list.
     * @return: A new interval list.
     */

     /*
     similar to the validation of parethese : ()(())(((()())))
     we need a stack
     
     
     another simpler solution is to sort in place than merge one by one
     
     */

    vector<vector<int>> merge_with_inplace_sort(vector<vector<int>>& intervals) 
    {
        vector<vector<int>> merged;
        //sort intervals then merge one by one
        sort(intervals.begin(), intervals.end(),[](const vector<int> & left, const vector<int> & right)
             {
                 return left[0]<right[0];
             });
        
        vector<int> currentInterval = intervals[0];
        
        for(int i = 1; i<intervals.size(); ++i)
        {
            if(intervals[i][0]<= currentInterval[1])
            {
                currentInterval[1] = max(intervals[i][1], currentInterval[1]);
            }
            else
            {
                merged.push_back(currentInterval);
                currentInterval = intervals[i];
            }
        }
        merged.push_back(currentInterval);
        
        return merged;
    }
    

    
    
    
    
    vector<Interval> merge(vector<Interval> &intervals) {
        // map to sort then merge
        map<int, int> axe;
        for(const auto & interval : intervals) 
        {
            ++axe[interval.start] ;//open
            --axe[interval.end];//close
        }

        vector<Interval> result;
        std::stack<int> openIntervalFroms;
        for(  auto it = axe.begin(); it!=axe.end(); ++it)
        {
            if(it->second > 0)
            {
                while(it->second>0)
                {
                    --it->second;
                    openIntervalFroms.push(it->first);
                }
            }
            else if(it->second < 0)
            {
                while(it->second<0)
                {
                    ++it->second;
                    if(openIntervalFroms.size() == 1)
                    {   
                        int from = openIntervalFroms.top();
                        int to = it->first;
                        result.emplace_back(from, to);
                    }
                    openIntervalFroms.pop();
                }
            }
            else
            {
                if(openIntervalFroms.empty())
                {
                    result.emplace_back(it->first, it->first);
                }
            }
        }
        return result;

    }
};
