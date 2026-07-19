class Solution {
private:
    void dfs(int cur,
        vector<int>& visited,
        const vector<vector<int>>& neighbors){
        
        visited[cur] = 1;
        for(auto next : neighbors[cur]) if(!visited[next]) dfs(next, visited, neighbors);
    }
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> neighbors(n);
        for(auto edge : edges){
            neighbors[edge[0]].push_back(edge[1]);
            neighbors[edge[1]].push_back(edge[0]);
        }
        
        vector<int> visited(n);
        int cluster = 0;
        for(int i=0; i<n; ++i){
            if(!visited[i]){
                ++cluster;
                dfs(i, visited, neighbors);
            }
        }
        return cluster;
    }
};
