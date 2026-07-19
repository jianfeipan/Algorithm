class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // adj[u] stores pairs of {weight, v}
        using W = int;
        using V = int;
        using E = pair<W, V>;
        vector<vector<E>> adj(n);
        for (const auto& time : times) {
            const auto u = time[0] - 1;
            const auto v = time[1] - 1;
            const auto w = time[2];
            adj[u].push_back({w, v});
        }
        
        k = k - 1; // Convert to 0-indexed

        // Stores minimum distance from k to all other nodes
        vector<int> min_from_k_to(n, INT_MAX);
        vector<int> min_prev(n, -1); // if we want to know the path
        
        min_from_k_to[k] = 0;
        min_prev[k] = k;

        // Min-heap storing pairs of {total_distance, node}
        priority_queue<E, vector<E>, greater<E>> min_heap_from_k; // take the nearst node to k
        min_heap_from_k.push({0, k});

        vector<char> visited(n, false);

        while (!min_heap_from_k.empty()) {
            auto [k_to_u, u] = min_heap_from_k.top(); min_heap_from_k.pop();

            // the different pathes could be pushed into the heap multipal time, ignore them if it doesn't make the global distance shorter
            if (k_to_u > min_from_k_to[u]) continue; 

            // this edge makes u shorter to k, check u's neighbors
            for (const auto& [u_to_v, v] : adj[u]) {

                // This edge shorts the distance to v, let's take it.
                auto k_to_v = min_from_k_to[u] + u_to_v;
                if ( k_to_v < min_from_k_to[v]) {
                    min_from_k_to[v] = k_to_v;
                    min_prev[v] = u;
                    min_heap_from_k.push({min_from_k_to[v], v}); // Push TOTAL distance, not  edge weight
                }
            }
        }

        // Find the maximum time it takes to reach any node
        int max_delay = *max_element(min_from_k_to.begin(), min_from_k_to.end());
        
        // If any node is unreachable, return -1
        return max_delay == INT_MAX ? -1 : max_delay;
    }
};