class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) 
    {
        if(n==1) return {0};
        if(n==2) return {0,1};
        
        unordered_map<int, unordered_set<int>> adjacents;
        for(const auto & edge : edges) 
        {
            adjacents[edge[0]].insert(edge[1]);
            adjacents[edge[1]].insert(edge[0]);
        }
        
        
        while(adjacents.size()>2)
        {
            vector<int> toCut;
            for(auto & [node, neighbors] : adjacents)
            {
                if(neighbors.size() == 1)
                {
                    toCut.push_back(node);
                }
            }
            
            for(int toCutNode : toCut)
            {
                const auto & neighbors = adjacents[toCutNode];
                for(auto & neighbor : neighbors)
                {
                    adjacents[neighbor].erase(toCutNode);
                }
                //cout<<"remove: "<<toCutNode<<endl;
                adjacents.erase(toCutNode);
            }
        }
        vector<int> minHightTreesRoots;minHightTreesRoots.reserve(adjacents.size());
        
        for(auto & [node,neighbors] : adjacents) minHightTreesRoots.push_back(node);
            
        return minHightTreesRoots;
        
    }
};
