#include <algorithm>
class Solution_BF_time_out {
/*
Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]

         200             1250      1300                  3200
0.       ->|
1                                   ->|
2                         ->|
3                                                         -->|

back track: DFS
every course: greedy to take  or if not go to next
*/


private:

    int _dfs_on_course(const vector<vector<int>>& courses, 
                        int courseIndex, 
                        int currentEnd){
        if(courseIndex == courses.size()) return 0;

        int maxCourses=0;;

        //take the current course
        if(currentEnd+courses[courseIndex][0] <= courses[courseIndex][1]){
            maxCourses = std::max(maxCourses, 
                1+_dfs_on_course(courses, courseIndex+1, currentEnd + courses[courseIndex][0])
            );
        }
        //skip the current course
        maxCourses = std::max(maxCourses,
            _dfs_on_course(courses, courseIndex+1, currentEnd) 
        );
        
        return maxCourses;
    }
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        //start with the tasks has a closer deadline.
        sort(courses.begin(), courses.end(), [](const vector<int>& left, const vector<int>& right){
            return left[1]<right[1];
        });

        return _dfs_on_course(courses, 0, 0);

    }
};

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 1. Sort courses by their deadline (lastDay)
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        priority_queue<int> pq; // Max-heap to track durations of selected courses
        int totalTime = 0;

        for (const auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            // Add the current course to our schedule
            totalTime += duration;
            pq.push(duration);

            // If we exceeded the deadline, drop the longest course we've taken so far
            if (totalTime > lastDay) {
                totalTime -= pq.top();
                pq.pop();
            }
        }

        // The size of the heap is the maximum number of courses we can take
        return pq.size();
    }
};
