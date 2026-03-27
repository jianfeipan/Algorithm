/*
You are given an integer n. There are n rooms numbered from 0 to n - 1.

You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.

Meetings are allocated to rooms in the following manner:

Each meeting will take place in the unused room with the lowest number.
If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
When a room becomes unused, meetings that have an earlier original start time should be given the room.
Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.

A half-closed interval [a, b) is the interval between a and b including a and not including b.

 

Example 1:

Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0. 
Example 2:

Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1. 

*/


/*
facts:
    - meetings in a queue is FIFO ordered by start time
    - rooms released is in queue in number order (smaller be consumed first)

idea:
    - sort meetings by start time: FIFO queue for meetins
    - have a minHeap for free room numbers. 
    - room vector can be used for meeitng count
    - simulate the event, 

*/
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end()); // mlogm
        vector<int> rooms(n);

        /*
        two minHeaps one for free and one for occupied
        but simpler way is just loop on the room vector, check which one to take
        or delay m*nlogn
        */

        using Room = int;
        priority_queue<Room, vector<Room>, greater<Room>> free; 
        using RoomEndTime = vector<long long>;
        priority_queue<RoomEndTime, vector<RoomEndTime>, greater<RoomEndTime>> occupied; 
        // used rooms: {end, roomNumber} greater on vector gives:
        //  min by end, then min roomNumber
        for(Room room=0; room<n; ++room) free.push(room);

        for(int i=0; i<meetings.size(); ++i){
            auto& currentTime = meetings[i][0];
            auto& currentEnd = meetings[i][1];
            
            // nlogn (room numbers)
            while(!occupied.empty() && occupied.top()[0] <= currentTime){
                free.push(occupied.top()[1]); // at current time free all finished rooms
                
                //cout<< "time:"<< occupied.top()[0] << " free: " <<occupied.top()[1]<<endl;

                occupied.pop();
            }

            if(!free.empty()){
                auto room = free.top();
                
                //cout<< "time:"<< currentTime << " pick: " <<room<<endl;
                
                free.pop();
                occupied.push({currentEnd, room});

                ++rooms[room];
            }else{                
                // no free with curent StartTime:  delay to next free room: 
                const auto earliestEnd = occupied.top()[0];
                const auto room = occupied.top()[1];
                const long long len = currentEnd-currentTime;
                const long long newEndTime = earliestEnd + len;
                
                //cout<< "time:"<< earliestEnd << " release and pick" <<room<<endl;
                
                occupied.pop();
                occupied.push({newEndTime, room});
                ++rooms[room];
            }
        }

        int mostMeeting = 0;
        int roomNumber = 0;
        for(int i=0; i<n; ++i){
            if(rooms[i]>mostMeeting){
                mostMeeting = rooms[i];
                roomNumber =i;
            }
        }

        return roomNumber;
    }
};

// better solution looping on the room vector from 0 to n-1
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        vector<int> roomUsed(n);
        vector<long long> roomFreeAt(n);

        for (int m=0; m < meetings.size(); ++m) {
            int start = meetings[m][0];
            int end = meetings[m][1];
            long long len = end - start;

            int room = -1;
            long long earliest = LLONG_MAX;
            int earliestRoom = -1;

            for (int i = 0; i < n; i++) {
                if (roomFreeAt[i] < earliest) {
                    earliest = roomFreeAt[i];
                    earliestRoom = i;
                }
                if (roomFreeAt[i] <= start) {
                    room = i;
                    break;
                }
            }

            if (room != -1) { // we have a free room
                roomFreeAt[room] = end;
                count[room]++;
            } else { // take the earliestRoom and extend the end time of this room
                roomFreeAt[earliestRoom] += dur;
                count[earliestRoom]++;
            }

            itr++;
        }

        int max = 0, idx = 0;
        for (int i = 0; i < n; i++) {
            if (count[i] > max) {
                max = count[i];
                idx = i;
            }
        }

        return idx;
    }
};
