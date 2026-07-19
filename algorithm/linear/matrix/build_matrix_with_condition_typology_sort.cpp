class Solution {
private:
    vector<int> topoSort(int k, vector<vector<int>>& edges) {
        vector<int> indegree(k + 1, 0);
        vector<vector<int>> adj(k + 1);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }

        queue<int> q;
        vector<int> order;
        for (int i = 1; i <= k; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            for (int nei : adj[node]) {
                indegree[nei]--;
                if (indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        if (order.size() != k) return {};
        return order;
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> rowOrder = topoSort(k, rowConditions);
        if (rowOrder.size() != k) return {};

        for(int  e: rowOrder) cout<< e<<", ";
        cout<<endl;

        vector<int> colOrder = topoSort(k, colConditions);
        if (colOrder.size() != k) return {};

        for(int  e: colOrder) cout<< e<<", ";
        cout<<endl;
        /*
        K numbers put in K*K matrix, we are good to put one number per col or per row,
        so we don't need to care if 1,2 are on left of 3, should I put 1,2 on the same col
        bla bla, we can safely say, let from left to right be 1,2,3, 1,2 can take differnt col
        cause we have enough space

        in this case using typological sort we could have two order 

                   0  1  2
        row order: 2, 1, 3, 
        col order: 2, 3, 1, 

        this two orders should be size k, other wise there is circular dependency and output []
        the two orders basically tell us value should be on which Row and which col: value Pos

          2 3 1
        2 2
        1     1
        3   3

        -> basically translate to value's positions: 2 should be (0,0) 1 should b2 (1, 3)  ..
        */

        vector<vector<int>> res(k, vector<int>(k, 0));
        using Row = int;
        using Col = int;
        vector<pair<Row, Col>> valuePos(k+1);
        for(int i=0; i<k; ++i){
            auto& rowValue = rowOrder[i];
            valuePos[rowValue].first = i;
            auto& colValue = colOrder[i];
            valuePos[colValue].second = i;
        }
        for(int i=1; i<=k; ++i){
            const auto& [r, c] = valuePos[i];
            res[r][c] = i;
        }

        
        return res;
    }
};
