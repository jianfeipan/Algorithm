class Solution {// Dijikstra
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        using Time = int;
        using From = int;
        using To = int;
        using Edge = pair<Time, To>;
        unordered_map<From, vector<Edge>> edges;
        for(const auto& u_v_t : times) edges[u_v_t[0]].emplace_back(u_v_t[2], u_v_t[1]);

        using TimeFromK = int;
        using Path = pair<TimeFromK, To>;
        priority_queue<Path, vector<Path>, greater<>> minHeap;


        vector<int> min_k_to(n+1, INT_MAX);
        vector<int> min_prev(n+1, 0);
        // start from k
        minHeap.push({0, k});
        min_k_to[k] = 0; 
        min_prev[k] = k;
        
        
        while(!minHeap.empty()){
            const auto [t, cur] = minHeap.top();minHeap.pop();
            if(t > min_k_to[cur]) continue; // visited or not shortest
            
            for(auto [cur_to_next, next] : edges[cur]){
                auto k_to_next = min_k_to[cur] + cur_to_next;
                if(k_to_next < min_k_to[next]){

                    min_k_to[next] = k_to_next;
                    min_prev[next] = cur;

                    minHeap.push({k_to_next, next}); // !! in the priority queue the time is the time from K!!
                }
            }
        }
        int delay = *max_element(++min_k_to.begin(), min_k_to.end());
        return delay == INT_MAX ? -1 : delay;
    }
};
