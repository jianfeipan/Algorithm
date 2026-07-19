
/*
problem:

There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each node has a value associated with it, and the root of the tree is node 0.

To represent this tree, you are given an integer array nums and a 2D array edges. Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.

Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.

An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.

Return an array ans of size n, where ans[i] is the closest ancestor to node i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such ancestor.

*/
class Solution {
public:
    //a solution for edges are with directions
    vector<int> getCoprimes_directionEdges(vector<int>& nums, vector<vector<int>>& edges) {
        vector<int> ancestor(nums.size(), -1);
        /*
        example : 
        0 -> -1    
        1 -> 0
        2 -> 1
        3 -> 1 
        */
        
        for(int index = 0; index < nums.size(); ++index)
        {
            for(const auto & edge : edges)
            {
                if(edge[1] == index)
                {
                    ancestor[index] = edge[0];
                    break;
                }
            }
            
        }
        
        
        vector<int> coprimes = ancestor;
        for(int index = 0; index < nums.size(); ++index)
        {
            //find coprimes for every node
            int currentAncentor = ancestor[index];
            int coprimeIndex = -1;
            
            while(currentAncentor>-1)
            {
                if(std::gcd(nums[index], nums[currentAncentor]) == 1)
                {
                    coprimeIndex = currentAncentor;
                    break;
                }
                
                currentAncentor = ancestor[currentAncentor];
            }
            
            coprimes[index] = coprimeIndex;
        }
        
        return coprimes;
        
    }
    
    //recutive discover the graph : N*N*logN
    void discoverChildrenFrom(int parent, vector<int> & ancestor, const vector<vector<int>>& edges){
        set<int> children;
        //find children
        for(const auto & edge : edges)
        {
            if(edge[0] == parent && edge[1]!=ancestor[parent])
            {
                children.insert(edge[1]);
            }
            else if(edge[1] == parent &&  edge[0]!=ancestor[parent])
            {
                children.insert(edge[0]);
            }
        }
        
        for(int child : children)
        {
            ancestor[child] = parent;
        }
        
        for(int child : children)
        {
            discoverChildrenFrom(child, ancestor, edges);
        }
    }
    vector<int> getCoprimes_TimeLimitExceeded(vector<int>& nums, vector<vector<int>>& edges/*no direction, 0 is always the root*/) {
        vector<int> ancestor(nums.size(), -1);
        /*
        example : 
        0 -> -1    
        1 -> 0
        2 -> 1
        3 -> 1 
        */
        
        discoverChildrenFrom(0, ancestor, edges);
        
        vector<int> coprimes = ancestor;
        for(int index = 0; index < nums.size(); ++index)
        {
            //find coprimes for every node
            int currentAncentor = ancestor[index];
            int coprimeIndex = -1;
            
            while(currentAncentor>-1)
            {
                if(std::gcd(nums[index], nums[currentAncentor]) == 1)
                {
                    coprimeIndex = currentAncentor;
                    break;
                }
                
                currentAncentor = ancestor[currentAncentor];
            }
            coprimes[index] = coprimeIndex;
        }
        return coprimes;
    }
    
    
    //transforme edges to bit map to make recutive better : N*logN
    void discoverChildrenFrom(int parent, vector<int> & ancestor, const  vector<set<int>>& connections){
        const set<int> & connectedNodes = connections[parent] ;
        
        for(int child : connectedNodes)
        {
            if(child != ancestor[parent])
            {
                ancestor[child] = parent;
                discoverChildrenFrom(child, ancestor, connections);
            }
        }
        
    }
    
    vector<int> getCoprimes_TimeLimitExceeded2(vector<int>& nums, vector<vector<int>>& edges/*no direction, 0 is always the root*/) {
        vector<int> ancestor(nums.size(), -1);
        /*
        example : 
        0 -> -1    
        1 -> 0
        2 -> 1
        3 -> 1 
        */
        vector< set<int> > connections(nums.size(), set<int>());
        
        for(const auto & edge : edges)
        {
            connections[edge[0]].insert(edge[1]);
            connections[edge[1]].insert(edge[0]);
        }
        
        discoverChildrenFrom(0, ancestor, connections);
        
        vector<int> coprimes = ancestor;
        for(int index = 0; index < nums.size(); ++index)
        {
            //find coprimes for every node
            int currentAncentor = ancestor[index];
            int coprimeIndex = -1;
            
            while(currentAncentor>-1)
            {
                if(std::gcd(nums[index], nums[currentAncentor]) == 1)// too many redondant computes
                {
                    coprimeIndex = currentAncentor;
                    break;
                }
                
                currentAncentor = ancestor[currentAncentor];
            }
            coprimes[index] = coprimeIndex;
        }
        return coprimes;
    }
    
    
    //possible improvement ?--> yes from 64% to 71%
    int gcd(int a, int b) {
        if (!a) return b;
        if (!b) return a;
        if (a > b) swap(a,b);
        return gcd(a,b%a); 
    }
    
    
    //-------------------------------------------passed solution
    
    
    
    //use a map to store compute results (all the possible values are computed)
    unordered_map<int, set<int>> cops;
    
    /*for a given value, the possible copr's level and index*/
    unordered_map<int/*a vlue*/, vector<pair<int/*level*/, int/*index*/>>>  ancestors;
    /*level is used to find which is the closest*/
    
    
    
    void dfs(const vector<int>& nums, const vector<set<int>> &connections, int current, int parent, int level, vector<int> &res) {
        
        //
        int max_level = -1;
        for (auto cop : cops[nums[current]]) {
            auto &v = ancestors[cop];
            if (!v.empty() && v.back().first > max_level) {
                max_level = v.back().first;
                res[current] = v.back().second;
            }
        }
        
        //dfs
        ancestors[nums[current]].push_back({level, current});
        for (auto child : connections[current])
            if (child != parent)
                dfs(nums, connections, child, current, level + 1, res);
        ancestors[nums[current]].pop_back();
    }
    
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges/*no direction, 0 is always the root*/) {
        
        unordered_set<int> s(begin(nums), end(nums));
        for (auto n1 : s) {
            for (auto n2 : s)
                if (gcd(n1, n2) == 1)
                    cops[n1].insert(n2);
        }
        
        
        vector< set<int> > connections(nums.size(), set<int>());
        
        for(const auto & edge : edges)
        {
            connections[edge[0]].insert(edge[1]);
            connections[edge[1]].insert(edge[0]);
        }
        
        
        vector<int> res(nums.size(), -1);
        
        dfs(nums, connections, 0, 0, 0, res);
        
        return res;
    }
};
