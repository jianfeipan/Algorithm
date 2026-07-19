class DUS{
    vector<int> m_parent; //node i's parent is parent[i-1]
    vector<int> m_rank; // who has more childre, who will be the parent
public:
    DUS(int n):m_parent(n, 0), m_rank(n, 0){
        for(int i=0; i<n; ++i){
            m_parent[i] = i;
        }
    }

    int parent(int i){
        int current = i;
        while(current!=m_parent[current]){
            current = m_parent[current];
        }
        return current;
    }

    bool tryUnionNodes(int left, int right){
        int leftParent = parent(left);
        int rightParent = parent(right);
        if(leftParent == rightParent) 
            return false; // they are already in the same set
        
        // union the two set:
        if(m_rank[leftParent]>m_rank[rightParent]){
            m_parent[rightParent] = leftParent;
            m_rank[leftParent]+=m_rank[rightParent];
        }else{
            m_parent[leftParent] = rightParent;
            m_rank[rightParent]+=m_rank[leftParent];

        }
        return true;
    }

};

class Solution {
/*
idea:
    add edge, and check if this edge makes a cycle
    "If there are multiple answers, return the edge that appears last in the input edges."
    -> Input: edges = [[1,2],[1,3],[1,4],[3,4],[4,5]]
    Output: [3,4] -> when 3.4 added, there is already the cycle, I don't care 4,5, I found [3,4]

    so we are detecting a cycle during adding edges, Disjoint Union Set should help:
    we continue to joinUnion, they should be from different sets, and if they are already in one set
    , this edge wll add a cycle!!!!

    Time complexity: 
O(V+(E∗α(V)))
Space complexity: O(V)
Where 
V is the number of vertices and 
E is the number of edges in the graph. 
α() is used for amortized complexity.
*/
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DUS dus(edges.size());

        // build DUS: O(V)
        // join: alpha(V) 
        // join for all edges: O(E*alpha(V))
        // total: 
        //        O(E * alpha(V) + V)
        //  alpha = inversed Arckemen function: grows slowly than first order: with flatten, it's ~=O(1)
        
        for(const auto& edge : edges){
            if(!dus.tryUnionNodes(edge[0]-1, edge[1]-1)){
                return edge;
            }
        }
        return {};//should not reach here
    }
};
