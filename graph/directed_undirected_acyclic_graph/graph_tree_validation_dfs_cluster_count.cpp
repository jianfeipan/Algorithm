class Solution {
private:
    bool has_circle(int cur,  
                    int prev,
                    const vector<vector<int>> & neighbors,
                    vector<char>& visited, 
                    vector<char>& current_path) {
        if (visited[cur]) return false; 
        if (current_path[cur]) return true;

        current_path[cur] = true;
        for(auto next : neighbors[cur]) {
            if(next == prev) continue; // skip back edge
            if(has_circle(next, cur, neighbors, visited, current_path)) return true;
        }
        current_path[cur] = false;

        visited[cur] = true;
        return false;

    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // no circle, and all connected
        // option 1: from one node, check if circle, and check if all visited
        // option 2: DSU: use edges add nodes, if edge join two nodes already in the same union-> circle. all nodes has the same parent-> connected
        vector<vector<int>> neighbors(n);

        for (auto& edge : edges) {
            neighbors[edge[0]].push_back(edge[1]);
            neighbors[edge[1]].push_back(edge[0]);
        }

        // heck circle
        vector<char> visited(n, false);
        vector<char> current_path(n, false);
        if(has_circle(0, -1, neighbors, visited, current_path)) return false;

        // check connected
        for(int node=0; node<n; ++node) {
            if(!visited[node]) return false;
        }

        return true;
    }
};


/*

Graph Valid Tree
Medium Topics Company Tags
Hints

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

Example 1:

Input:
n = 5
edges = [[0, 1], [0, 2], [0, 3], [1, 4]]

Output:
true

Example 2:

Input:
n = 5
edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]

Output:
false

Note:

    You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Constraints:    

*/