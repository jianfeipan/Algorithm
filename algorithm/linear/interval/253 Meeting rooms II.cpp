/*
Meeting Rooms II
Given an array of meeting time interval objects consisting of start and end times [[start_1,end_1],[start_2,end_2],...] (start_i < end_i), find the minimum number of rooms required to schedule all meetings without any conflicts.

Note: (0,8),(8,10) is NOT considered a conflict at 8.

Example 1:

Input: intervals = [(0,40),(5,10),(15,20)]

Output: 2
Explanation:
day1: (0,40)
day2: (5,10),(15,20)

Example 2:

Input: intervals = [(4,9)]

Output: 1
*/


/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */
class Solution {// sweapline
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> use_room;
        for(const auto& interval : intervals){
            use_room[interval.start] += 1; // take room
            use_room[interval.end] -= 1; // release room
        }

        int room = 0;
        int max_room = 0;
        for(const auto& [_, use] : use_room){
            room+=use;
            max_room = max(max_room, room);
        }
        return max_room;
    }
};
