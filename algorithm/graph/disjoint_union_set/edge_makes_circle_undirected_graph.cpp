class Solution {// Disjoint Set Union
private:
    class DSU{
    private:
        vector<int> m_parent;
        vector<int> m_rank;
    public:
        DSU(size_t capacity): 
            m_parent(capacity),
            m_rank(capacity){
            
            for(size_t i=0; i<capacity; ++i) m_parent[i] = i;
        }

        int parent(int node){
            auto p = m_parent[node];
            while(p!=m_parent[p]) p=m_parent[p];
            
            m_parent[node] = p;
            return p;
        }

        bool is_connected(int left, int right){
            return parent(left) == parent(right);
        }

        bool join(int left, int right){
            auto left_p = parent(left); 
            auto right_p = parent(right);
            if(left_p == right_p) return false;

            if(m_rank[left_p] == m_rank[right_p]){
                ++m_rank[left_p]; 
            }

            if(m_rank[left_p] > m_rank[right_p]){
                m_parent[right_p] = left_p;
            }else{
                m_parent[left_p] = right_p;
            }
            return true;
        }
    };
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DSU dsu(128);

        for(const auto& edge : edges){
            auto left = edge[0];
            auto right = edge[1];

            if(!dsu.join(left, right)) return edge;
        }

        return {};
    }
};
