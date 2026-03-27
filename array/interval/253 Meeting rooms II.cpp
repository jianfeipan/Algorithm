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

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        using Time = int;
        map<Time, int> roomRequests;
        
        for(auto& interval : intervals){
            ++roomRequests[interval.start];
            --roomRequests[interval.end];
        }

        int maxRoom = 0;
        int currentRoom = 0;
        for(auto& [t, room] : roomRequests){
            currentRoom+=room;
            maxRoom = max(maxRoom, currentRoom);
        }
        return maxRoom;
    }
};
