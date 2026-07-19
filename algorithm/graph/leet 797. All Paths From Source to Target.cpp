class Solution {

/*
DAG : directed, acyclic Graph
*/

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) 
    {
        return allPathsSourceTarget_bfs(graph);
    }
    
    
    vector<vector<int>> allPathsSourceTarget_bfs(vector<vector<int>>& graph) 
    {
        vector<vector<int>> paths;

        const int target = graph.size()-1;
        queue<pair<int, vector<int>>> level;
        level.push({0, {0}});
        
        while(!level.empty())
        {
            const auto & node = level.front();
            if(node.first == target) paths.push_back(node.second);

            for(auto dest : graph[node.first])
            {
                vector<int> nextPath(node.second);nextPath.push_back(dest);
                level.push({dest, nextPath});
            }
            level.pop();//pay attention to the node, it was a reference and you cannot pop if you still use it.
        }
        
        return paths;
    }
        
    vector<vector<int>> allPathsSourceTarget_dfs(vector<vector<int>>& graph) 
    {
        vector<vector<int>> paths;
        const int start = 0;
        const int target =  graph.size()-1;
        allPathsSourceTarget_dfs(graph, start, target, {}, paths);
        
        return paths;
        
    }
    
    
private:
    void allPathsSourceTarget_dfs(const vector<vector<int>>& graph, 
                                  int current,
                                  int target,
                                  vector<int> currentPath,
                                  vector<vector<int>> & paths)
    {
        currentPath.push_back(current);
        if(current == target) 
        {
            paths.push_back(currentPath);
        }
        else
        {
            for(auto dest : graph[current])
            {
                allPathsSourceTarget_dfs(graph, dest, target, currentPath, paths);
            }
        }
    }
    
};
