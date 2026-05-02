/*
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

1 <= n <= 100
0 <= edges.length <= n * (n - 1) / 2


4
[[0,1],[2,3]] false

1
[] true

*/


class Solution {
/*
tree
1 no cycles: DFS
2 only one graph: cannot have 0-1 2-3

n=5
edges=[[0,1],[2,0],[3,0],[1,4]]

    0 
   /|\
  1 2 3
 /
4
*/
private:
    bool dfs_no_cycle(vector<vector<int>>& graph, vector<bool>& visited, int current, int prev){
        if(visited[current]) 
            return false; //cycle
        
        visited[current] = true;

        for(int neighbor : graph[current]){
            if(neighbor!=prev){// dont go back the the node you just come from
                if(!dfs_no_cycle(graph, visited, neighbor, current)){
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n, vector<int>());

        //bi-direction
        for(const auto& edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        if(!dfs_no_cycle(graph, visited, 0, -1)){
            return false;
        }

        for(bool v : visited){
            if(!v) return false;// some element not visitied from one point
        }
        return true;
    }
};
