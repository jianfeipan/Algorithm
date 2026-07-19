class Solution {
private:
    double distance(int x, int y) {
        return sqrt(x*x + y*y);
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        using Dist = double;
        using Point = vector<int>;
        priority_queue<pair<Dist, Point>> maxHeap;


        for (const auto& point : points) {
            const auto dist = distance(point[0], point[1]);

            // maxHeap.push({dist, point});
            // if( maxHeap.size() > k ) { 
            //     maxHeap.pop();
            // }
            
            // better perfromance
            if( maxHeap.size() < k ) {
                maxHeap.push({dist, point});
            } else {
                if (dist < maxHeap.top().first) {
                    maxHeap.pop(); maxHeap.push({dist, point});
                }
            }
        }
        vector<vector<int>> closest; closest.reserve(k);
        while (!maxHeap.empty()) {
            closest.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return closest;

    }
};
