/*
You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [aᵢ, bᵢ] indicates that there is an edge between aᵢ and bᵢ in the graph.

Return the number of connected components in the graph.

Example 1:



Input:
n = 5, edges = [[0,1],[1,2],[3,4]]

Output: 2
Example 2:



Input:
n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]

Output: 1
Constraints:

1 <= n <= 2000
1 <= edges.length <= 5000
edges[i].length == 2
0 <= aᵢ <= bᵢ < n
aᵢ != bᵢ
There are no repeated edges.

*/

class Solution_dfs {
/*
DFS visit
complexity: 

Where 
V
V is the number of vertices and 
E
E is the number of edges in the graph

time O(V+E)
space:O(V+E)
*/

private:
    void _dfs(const vector<vector<int>>& neighbor, 
            vector<bool>& visited,
            int current
            ){
        if(visited[current]) return;

        visited[current] = true;
        for(auto next : neighbor[current]){
            _dfs(neighbor, visited, next);
        }
    }
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<bool> visited(n, false);
        vector<vector<int>> neighbor(n, vector<int>());

        for(const auto& edge : edges){
            neighbor[edge[0]].push_back(edge[1]);
            neighbor[edge[1]].push_back(edge[0]);
        }

        int count = 0;
        for(int node=0; node<n; ++node){
            if(!visited[node]){
                ++count;
                _dfs(neighbor, visited, node);
            }
        }

        return count;
    }
};

/*
Disjoint Set Union
Union Set: 
each element has a parent, the parent of the union is the parent of itself
if they are in the same  union: has he same parent

*/
class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int node) {
        int cur = node;
        while (cur != parent[cur]) {
            parent[cur] = parent[parent[cur]];
            cur = parent[cur];
        }
        return cur;
    }

    bool unionSets(int u, int v) {
        // try to union the two sets
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) {
            return false;// they don't have the same parent
        }
        if (rank[pv] > rank[pu]) {
            swap(pu, pv);
        }
        parent[pv] = pu;
        rank[pu] += rank[pv];
        return true;
    }
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        DSU dsu(n);
        int sets = n;
        for (auto& edge : edges) {
            if (dsu.unionSets(edge[0], edge[1])) {
                --sets;// if it can be unioned, they are in the same component: less component count
            }
        }
        return sets;
    }
};


