/*
You are given a network of n directed nodes, labeled from 1 to n. You are also given times, a list of directed edges where times[i] = (ui, vi, ti).

ui is the source node (an integer from 1 to n)
vi is the target node (an integer from 1 to n)
ti is the time it takes for a signal to travel from the source to the target node (an integer greater than or equal to 0).
You are also given an integer k, representing the node that we will send a signal from.

Return the minimum time it takes for all of the n nodes to receive the signal. If it is impossible for all the nodes to receive the signal, return -1 instead.

Example 1:



Input: times = [[1,2,1],[2,3,1],[1,4,4],[3,4,1]], n = 4, k = 1

Output: 3
Example 2:

Input: times = [[1,2,1],[2,3,1]], n = 3, k = 2

Output: -1
Constraints:

1 <= k <= n <= 100
1 <= times.length <= 1000
*/

class Solution {//BFS: take closest neighbor

public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<int>> adjacent(n, vector<int>(n,-1));// network matrix
        for(const auto& time:times){
            adjacent[time[0]-1][time[1]-1] = time[2];
        }

        vector<int>  minDelayFromStartPoint(n, INT_MAX);// visited group to other nodes time,
        
        queue<int> q;
        q.push(k-1);
        minDelayFromStartPoint[k-1] = 0;
        while(!q.empty()){
            const int current = q.front();
            q.pop();

            for(int next=0; next<n; ++next){
                if(adjacent[current][next]!=-1){
                    int newDistance = minDelayFromStartPoint[current] + adjacent[current][next];
                    if(newDistance < minDelayFromStartPoint[next]){
                        minDelayFromStartPoint[next] = newDistance;
                        q.push(next);
                    }
                }
            }
        }
        int lastPointDelay = 0;
        for(int delay : minDelayFromStartPoint){
            lastPointDelay=max(delay, lastPointDelay);
        }   
        return lastPointDelay==INT_MAX ? -1 : lastPointDelay;
    }
};
