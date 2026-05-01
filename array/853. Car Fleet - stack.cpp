/*
There are n cars traveling to the same destination on a one-lane highway.

You are given two arrays of integers position and speed, both of length n.

position[i] is the position of the ith car (in miles)
speed[i] is the speed of the ith car (in miles per hour)
The destination is at position target miles.

A car can not pass another car ahead of it. It can only catch up to another car and then drive at the same speed as the car ahead of it.

A car fleet is a non-empty set of cars driving at the same position and same speed. A single car is also considered a car fleet.

If a car catches up to a car fleet the moment the fleet reaches the destination, then the car is considered to be part of the fleet.

Return the number of different car fleets that will arrive at the destination.

Example 1:

Input: target = 10, position = [1,4], speed = [3,2]

Output: 1
Explanation: The cars starting at 1 (speed 3) and 4 (speed 2) become a fleet, meeting each other at 10, the destination.

Example 2:

Input: target = 10, position = [4,1,0,7], speed = [2,2,1,1]

Output: 3
Explanation: The cars starting at 4 and 7 become a fleet at position 10. The cars starting at 1 and 0 never catch up to the car ahead of them. Thus, there are 3 car fleets that will arrive at the destination.

Constraints:

n == position.length == speed.length.
1 <= n <= 1000
0 < target <= 1000
0 < speed[i] <= 100
0 <= position[i] < target
All the values of position are unique.

*/



class Solution {
public:
    // "die frage ist nicht wo sondern wann"
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // Dont bother with the pos, it's hard to track the
        // the key is the time: 
        //  if you want to track pos, you need to know how long it takes for each fleet
        //  but we don't know yet how many fleet or how long we need for the first car to reach target for that fleet.
        //  However, time can be tracked: the target is fixed!
        //  "die frage ist nicht wo sondern wann" 
        //. imaging their are independent and they all have a estimated time to reach target. 
        // then we loop from the head car check if the time is smaller then the back car

        //"If a car catches up to a car fleet the moment the fleet reaches the destination, then the car is considered to be part of the fleet."
        // this need the current car reach the target to be considered in that fleet.

        using Pos = int;
        using Speed = int;
        vector<pair<Pos, Speed>> orderedCars;
        orderedCars.reserve(position.size());
        for(int i = 0; i<position.size(); ++i){
            orderedCars.push_back({position[i], speed[i]});
        }
        sort(orderedCars.rbegin(), orderedCars.rend());
        //r!!!! from big to small, from cars closer to target

        stack<double> time;
        for(const auto & [pos, speed] : orderedCars){
            const auto current = (double)(target - pos) / speed;
            if(time.empty() || current>time.top()){
                // current car won't catch the front Fleet, push it to the stack, there will be a new Fleet
                time.push(current);
            }
        }
        

        return time.size();
    }
};
