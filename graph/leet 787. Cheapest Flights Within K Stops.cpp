/*
There are n airports, labeled from 0 to n - 1, which are connected by some flights. You are given an array flights where flights[i] = [from_i, to_i, price_i] represents a one-way flight from airport from_i to airport to_i with cost price_i. You may assume there are no duplicate flights and no flights from an airport to itself.

You are also given three integers src, dst, and k where:

src is the starting airport
dst is the destination airport
src != dst
k is the maximum number of stops you can make (not including src and dst)
Return the cheapest price from src to dst with at most k stops, or return -1 if it is impossible.

Example 1:



Input: n = 4, flights = [[0,1,200],[1,2,100],[1,3,300],[2,3,100]], src = 0, dst = 3, k = 1

Output: 500
Explanation:
The optimal path with at most 1 stop from airport 0 to 3 is shown in red, with total cost 200 + 300 = 500.
Note that the path [0 -> 1 -> 2 -> 3] costs only 400, and thus is cheaper, but it requires 2 stops, which is more than k.

Example 2:



Input: n = 3, flights = [[1,0,100],[1,2,200],[0,2,100]], src = 1, dst = 2, k = 1

Output: 200
Explanation:
The optimal path with at most 1 stop from airport 1 to 2 is shown in red and has cost 200.

Constraints:

1 <= n <= 100
fromi != toi
1 <= pricei <= 1000
0 <= src, dst, k < n
*/

/*
facts:

    we have a graph, 
    nodes, edges and costs on edges
    * could have circle. 

    I have start point, end point, K steps
    find the shortest path

idea:
    DFS/BFS: 
        DFS will go over all possible pathes under k depth, which is V^k
        in a problem with limited depth or find shortest path, BFS is more straight forward
    with visited to avoid circle;??? -> see later comment in the code
    depth counter to stop at K ;
    variable  to find min;

    corner case: 
        if cannot find: return -1? 
        could have several cheapest path, I just treutrn the price

    
*/
class Solution {
    //BFS: O(n*k) space O(n+m)
//SPFA (Shortest Path Faster Algorithm) is essentially a queue-optimized Bellman–Ford.
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        using Stops=int;
        using Cost = int;
        using Node=int;
        vector<Cost> minCostFromSrc(n, INT_MAX);
        minCostFromSrc[src] = 0;
        // grah: adj table or hash map
        vector<vector<pair<Node, Cost>>> flight_cost(n); // -1 is unreachable

        for(const auto & flight : flights){
            const auto& from = flight[0];
            const auto& to = flight[1];
            const auto& cost = flight[2];
            flight_cost[from].emplace_back(to, cost);
        }

        queue<tuple<Node, Cost, Stops>> q;
        q.push({src, 0, 0});
        /*
        0 --(1)--> 1 
          \        |(1)
           \       v
            (5)--> 2 --(1)-->3

        2 can be resued: so we cannot do the visited to avoid the circle.
        and we won't have a global level count to stop at k, because stops depends on path
        not the global level
        */
        while( !q.empty() ){ // the stops is not the level of BFS because we may reuse the node
            const auto& [current, currentCost, currentSteps] = q.front();
            q.pop();
            if(currentSteps>k) continue; 
            // ignore path more than k: 
            // this is important! we are not using a global level to stop, but depends on k

            for(const auto& [next, cost] : flight_cost[current]){
                const auto& nextCost = currentCost+cost;
                if(nextCost < minCostFromSrc[next]) {// will using this next make it shorter?
                    minCostFromSrc[next] = nextCost;
                    q.push({next, nextCost, currentSteps+1});
                }
            }
        }
        return minCostFromSrc[dst]==INT_MAX? -1 : minCostFromSrc[dst] ;

    }
};
