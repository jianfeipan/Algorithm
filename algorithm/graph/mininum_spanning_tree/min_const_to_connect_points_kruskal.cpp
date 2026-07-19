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

class DUS {
private:
    vector<int> parent;
    vector<int> rank;   
public:
    DUS(int capacity) : parent(capacity), rank(capacity){
        for(int i=0; i<capacity; ++i) parent[i] = i;
    }

    int get_parent(int node){
        auto p = parent[node];
        while(p != parent[p]){
            p = parent[p];
        }
        parent[node] = p;
        return p;
    }

    bool join(int left, int right){
        auto left_p = get_parent(left);
        auto right_p = get_parent(right);

        if(left_p == right_p) return false;

        if(rank[left_p] == rank[right_p]) ++rank[left_p];
            
        if(rank[left_p] < rank[right_p]) parent[left_p] = right_p;
        else parent[right_p] = left_p;

        return true;
    }
};

class Solution {// kruskal

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const auto n = points.size();
        auto distance = [&points](int from, int to){
            return abs(points[from][0] - points[to][0]) + abs(points[from][1] - points[to][1]);
        };
        
        vector<tuple<int, int, int>> edges;edges.reserve(n*(n-1));
        for(int from=0; from<n; ++from){
            for(int to=from+1; to<n; ++to){
                edges.emplace_back(distance(from, to), from, to);
            }
        }
        sort(edges.begin(), edges.end());

        DUS dus(n);
        int sum=0;
        for(auto &[dist, from, to] : edges){
            if(dus.join(from, to)){
                sum+=dist;
            }
        }
        
        return sum;
        
    }
};
