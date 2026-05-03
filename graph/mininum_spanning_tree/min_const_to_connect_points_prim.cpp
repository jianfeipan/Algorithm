/*
MST, global

1 Kruskal's Algorithm: a global vision
    sort all edges(n^2), take smallest one, (n^2 * logn)
    check if the edges join two different set with Disjoint Union Set (logn)
    until all nodes in the same union
    n^2 logn  

2 Prim: : from one point to build the tree
    start from one point, similar to Dijkstra but take the min distance to the tree!!, not the starting nod
    the min distance to the tree is actually all the edges (n^2) of the "frontier" minHeap logn
    n^2 logn   

3 Prim optimal: all nodes are connected: no need to do minHeap
    every node is connected to every node, so minHeap doesn't helps,
    we just need to compute current node to all other node's distance: n and note the min
    then do this util all nodes visited: n
    n^2
*/
class Solution {// Prime optimal

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const auto n = points.size();
        auto distance = [&points](int from, int to){
            return abs(points[from][0] - points[to][0]) + abs(points[from][1] - points[to][1]);
        };

        vector<bool> visited(n, false);
        vector<int> tree_dist(n, INT_MAX);// distance to the MST
        int connected = 1;
        int cur = 0;
        int sum = 0;
        while(connected < n){
            visited[cur] = true;
            int min_next=-1;
            for(int next= 0; next<n; ++next){
                if(visited[next]) continue;
                auto dist = distance(cur, next);
                tree_dist[next] = min(tree_dist[next], dist); // update global distance

                if(min_next == -1 || tree_dist[min_next] > tree_dist[next]){ // find global min
                    min_next = next;
                }
            }

            cur = min_next;
            sum+=tree_dist[min_next];
            ++connected;
        }
        return sum;
        
    }
};
