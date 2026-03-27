class Solution {
public:
    /*
    
    Time complexity: O(n^2)
    Space complexity:  O(n)

    */
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> minDist(n, INT_MAX);

        // unordered_set<int> 
        vector<bool> visited(n, false);
        int connectedNodes = 0;
        
        int curr = 0;
        minDist[curr] = 0;
        ++connectedNodes;
        while (connectedNodes < n) {
            visited[curr] = true;
            // if we don't have a lot of edges, we can use a minHeap to push all the frontier
            // here all nodes can be connected, so we loop all nodes instead minHeap
            int closest = -1;
            for (int i = 0; i < n; i++) {
                if (!visited[i]){
                    int curDist = abs(points[i][0] - points[curr][0])
                                + abs(points[i][1] - points[curr][1]);

                    // update mindist from visited group
                    minDist[i] = min(minDist[i], curDist);
                    // find cloest neighber to be next node
                    if (closest == -1 || minDist[i] < minDist[closest]) {
                        closest = i;
                    }
                }
                
            }
            curr = closest;
            connectedNodes++;
        }
        return std::accumulate(minDist.begin(), minDist.end(), 0);
    }
};
