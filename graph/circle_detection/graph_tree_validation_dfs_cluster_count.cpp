class Solution {// circle detection
private:
    bool dfs_has_cycle(
        int cur, 
        int prev, 
        vector<int>& validated, 
        vector<int>& current_path, 
        const vector<vector<int>>& neighbors){
        
        if(validated[cur]) return false;

        current_path[cur] = 1;
        for(auto next : neighbors[cur]){
            if(next == prev) continue; // don't go back-> this is different from directed DAG
            if(current_path[next]) return true;

            if(dfs_has_cycle(next, cur, validated, current_path, neighbors)) return true;
        }
        current_path[cur] = 0;
        
        validated[cur] = 1;
        return false;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> neighbors(n);
        for(auto edge : edges) { 
            neighbors[edge[1]].push_back(edge[0]);
            neighbors[edge[0]].push_back(edge[1]);
        }

        vector<int> validated(n);
        int cluster = 0;
        for(int i=0; i<n; ++i){
            if(!validated[i]){
                ++cluster;
                vector<int> current_path(n);
                current_path[i]=1;
                if(dfs_has_cycle(i, -1, validated, current_path, neighbors)) return false;
                current_path[i]=0;
            }
        }

        return cluster == 1;
    }
};
