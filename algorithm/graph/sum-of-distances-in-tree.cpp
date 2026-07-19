/*
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
*/
class Solution {
    
    vector<unordered_set<int>> tree;
    vector<int> res, count;
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        tree.resize(N);
        res.assign(N, 0);
        count.assign(N, 1);
        for (auto e : edges) {
            tree[e[0]].insert(e[1]);
            tree[e[1]].insert(e[0]);
        }
        dfs(0, -1);
        dfs2(0, -1);
        return res;

    }

    void dfs(int root, int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            dfs(i, root);
            count[root] += count[i];
            res[root] += res[i] + count[i];
        }
    }

    void dfs2(int root, int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            res[i] = res[root] - count[i] + count.size() - count[i];
            dfs2(i, root);
        }
    }
    
    
public:
    vector<int> sumOfDistancesInTreeSolution1(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> graph(n, vector<int>());

        for(const auto & edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        

        
        
       
        vector<int> sumDistances(n, 0);

        for(int i = 0; i < n; ++i)
        { 
           sumDistances[i] = sumDistanceFrom(i, graph);
        }
               
        return sumDistances;
    }
    
private:

    
    int sumDistanceFrom(int node, const vector<vector<int>> & graph) 
    {
        vector<bool> visited(graph.size(), false);
        int sum = 0;
        
        DFS(node, node, graph, visited, 0, sum);
        return sum;
    }
    
    void DFS(int from, int to,
             const vector<vector<int>> & graph,
             vector<bool>& visited,
             int distance,
             int & sum)
    {
        visited[to] = true;
        sum+=distance;
        for(const auto & neighber : graph[to])
        {
            if(!visited[neighber])
            {
                DFS(from, neighber, graph, visited, distance+1, sum);
            }
        }
    }
};
