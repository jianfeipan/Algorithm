class Solution { // tank from 0 move, if back to >0, can make it, 
// we start always from the next one after the lowest tank
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        const auto n = gas.size();
        //assert(cost.size() == n);
        int tank = 0;
        int min_tank = INT_MAX;
        int min_tank_index; 

        /*
            gas= [1, 2, 3,4,5]
            cost=[3, 4, 5,1,2]
            tank=[-2,-4 -6, -3, 0]
        */

        for(int i = 0; i < gas.size(); ++i){
            tank+=(gas[i] - cost[i]);
            if(min_tank > tank){
                min_tank = tank;
                min_tank_index = i;
            }
        }
        if(tank < 0) return -1;

        return min_tank_index == n-1 ? 0 : min_tank_index + 1;
    }
};


class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        /*
        try to find a start that can reach end,

        initialize  end to 0, 
                    start to n-1,
        try to check from current start if we can have a tank negative:
            if tank<0 try a earliler start start--
            if tank=> try go further :  end++

            when start meet end: we finished
                if tank < 0 : cannot do it.
                if tank < 
        */
        const auto& n = gas.size();
        int start = n-1;
        int end = 0;
        int tank = gas[start] - cost[start];

        while(start>end){
            if(tank<0){
                // start is not possible, in order to be able to reach start, 
                // we need to start earlier to get more gas in tank
                --start;
                tank += gas[start] - cost[start];
            }else{
                // this start is possible, wich means we can go further
                // let's extend end and see if we can go one more step
                ++end;
                tank += gas[end] - cost[end]
            }
        }
       
        // when start reaches end, if tank < 0; we don't find a way
        return tank<0? -1 : start;
    }
};
/*
There are n gas stations along a circular route. You are given two integer arrays gas and cost where:

gas[i] is the amount of gas at the ith station.
cost[i] is the amount of gas needed to travel from the ith station to the (i + 1)th station. (The last station is connected to the first station)
You have a car that can store an unlimited amount of gas, but you begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index such that you can travel around the circuit once in the clockwise direction. If it's impossible, then return -1.

It's guaranteed that at most one solution exists.

Example 1:

Input: gas = [1,2,3,4], cost = [2,2,4,1]

Output: 3
Explanation: Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 1 + 1 = 4
Travel to station 1. Your tank = 4 - 2 + 2 = 4
Travel to station 2. Your tank = 4 - 2 + 3 = 5
Travel to station 3. Your tank = 5 - 4 + 4 = 5

Example 2:

Input: gas = [1,2,3], cost = [2,3,2]

Output: -1
Explanation:
You can't start at station 0 or 1, since there isn't enough gas to travel to the next station.
If you start at station 2, you can move to station 0, and then station 1.
At station 1 your tank = 0 + 3 - 2 + 1 - 2 = 0.
You're stuck at station 1, so you can't travel around the circuit.

Constraints:

1 <= gas.length == cost.length <= 1000
0 <= gas[i], cost[i] <= 1000
*/
