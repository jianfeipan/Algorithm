/*
Find Critical and Pseudo Critical Edges in Minimum Spanning Tree
Hard
Topics
Company Tags
You are given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [a[i], b[i], weight[i]] represents a bidirectional and weighted edge between nodes a[i] and b[i]. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.

Example 1:

Input: n = 4, edges = [[0,3,2],[0,2,5],[1,2,4]]

Output: [[0,2,1],[]]
Example 2:

Input: n = 5, edges = [[0,3,2],[0,4,2],[1,3,2],[3,4,2],[2,3,1],[1,2,3],[0,1,1]]

Output: [[4,6],[0,1,2,3]]

Dijkstra
    from 0 with a frontier take only smallest until all nodes is connected...
    but this one is to find one MST, but helpful to identify critical or not critical
Kruskal:
    greedy:
    take smallest edge,
    there maybe several:
        if they cannot join different union : skip, no don't contribut to the MST
        if they are join the set : add to MST.

*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
using namespace std;

class Union{
private:
    int n;
    vector<int> par;
    vector<int> rnk;
public:
    Union(int size)
        : n(size)
        , par(n)
        , rnk(n, 0){
        for(int i=0; i<n; ++i) par[i] = i;
    }

    int find(int node){
        int root = node;
        while(root != par[root]) root = par[root];
        while(node != root) {           // second pass: faltten all
            int next = par[node];
            par[node] = root;
            node = next;
        }
        return root;
    }

    bool sameUnion(int left, int right){
        return find(left) == find(right);
    }

    bool join(int left, int right){
        auto leftParent = find(left);
        auto rightParent = find(right);

        if(leftParent == rightParent) return false;

        if(rnk[leftParent] < rnk[rightParent]){
            par[leftParent] = rightParent;
        }else if(rnk[leftParent] > rnk[rightParent]){
            par[rightParent] = leftParent;
        }else{
            par[rightParent] = leftParent;
            ++rnk[leftParent];
        }
        return true;
    }
};
class Solution {
private:

    using U = int;
    using V = int;
    using E = int;
    bool dfs(const unordered_map<U, unordered_map<V, E>>& mst,
        U from, V to, vector<E>& path, unordered_set<U>& visited){
        if(from == to) return true;

        for(const auto [next, edge] : mst.at(from)){
            if(!visited.count(next)){
                visited.insert(next);
                path.push_back(edge);
                if(dfs(mst, next, to, path, visited)) return true;
                visited.erase(next);
                path.pop_back();

            }
        }
        return false;

    }

    vector<E> findPath(const unordered_map<U, unordered_map<V, E>>& mst,
                       U from, V to){
        vector<E> path;
        unordered_set<V> visited;
        visited.insert(from);
        dfs(mst, from, to, path, visited);

        return path;
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        // find MST Kruskal: take smallest edge
        using Edge = vector<E>; //<Weight,From, To, Index>
        vector<Edge> sortedEdges;

        for(int idx = 0; idx<edges.size(); ++idx){
            const auto& from = edges[idx][0];
            const auto& to = edges[idx][1];
            const auto& weight = edges[idx][2];
            sortedEdges.push_back({weight, from, to, idx});
        }
        sort(sortedEdges.begin(), sortedEdges.end());


        unordered_map<U, unordered_map<V, E>> mst;
        unordered_set<E> mstEdges;
        Union unionFind(n);
        for(const auto& edge : sortedEdges){
            const auto& from = edge[1];
            const auto& to = edge[2];
            const auto& e = edge[3];
            if(!unionFind.sameUnion(from, to)){
                mst[from][to] = e;
                mst[to][from] = e;
                mstEdges.insert(e);
                unionFind.join(from, to);
            }
        }


        // based on current MST, every other edge's from to already has a path
        // any edge in this path has the same weight of this edge, they are not critical
        /*
             0 ---  1
                    |
                    |
             1  --- 2
            if they are all 3 and I have a edge not in MST is also 3,
            they are all pesudo critical:
                any of them can be removed (remove one) and won't change the wieght of MST
        */

        unordered_set<E> pesudoCritical;
        unordered_set<E> critical = mstEdges;

        for(const auto& edge : sortedEdges){
            const auto& edgeIndex = edge[3];
            if(!mstEdges.count(edgeIndex)){// not in mst
                const auto& weight = edge[0];
                const auto& from = edge[1];
                const auto& to = edge[2];

                auto edgesInPath = findPath(mst, from, to);
                bool findSameWeight = false;
                for(const auto& e : edgesInPath){
                    if(weight == edges[e][2]){
                        findSameWeight = true;
                        pesudoCritical.insert(e);
                        critical.erase(e);
                    }
                }
                if(findSameWeight) pesudoCritical.insert(edgeIndex);
            }
        }

        return {
            vector<E>(critical.begin(), critical.end()),
            vector<E>(pesudoCritical.begin(), pesudoCritical.end())
        };


    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < (int)result.size(); ++i) {
        cout << "[";
        for (int j = 0; j < (int)result[i].size(); ++j) {
            cout << result[i][j];
            if (j + 1 < (int)result[i].size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < (int)result.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Example 1: n=4, edges=[[0,3,2],[0,2,5],[1,2,4]]
    // Expected: [[0,2,1],[]]  (all critical, no pseudo-critical)
    {
        int n = 4;
        vector<vector<int>> edges = {{0,3,2},{0,2,5},{1,2,4}};
        cout << "Test 1: ";
        printResult(sol.findCriticalAndPseudoCriticalEdges(n, edges));
    }

    // Example 2: n=5, edges=[[0,3,2],[0,4,2],[1,3,2],[3,4,2],[2,3,1],[1,2,3],[0,1,1]]
    // Expected: [[4,6],[0,1,2,3]]
    {
        int n = 5;
        vector<vector<int>> edges = {{0,3,2},{0,4,2},{1,3,2},{3,4,2},{2,3,1},{1,2,3},{0,1,1}};
        cout << "Test 2: ";
        printResult(sol.findCriticalAndPseudoCriticalEdges(n, edges));
    }

    return 0;
}
