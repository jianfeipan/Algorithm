/*
You are given an 2-D array points where points[i] = [xi, yi] represents the coordinates of a point on an X-Y axis plane. 
You are also given an integer k.

Return the k closest points to the origin (0, 0).

The distance between two points is defined as the Euclidean distance 
(sqrt((x1 - x2)^2 + (y1 - y2)^2)).

You may return the answer in any order.

Example 1:



Input: points = [[0,2],[2,2]], k = 1

Output: [[0,2]]
Explanation : The distance between (0, 2) and the origin (0, 0) is 2. The distance between (2, 2) and the origin is sqrt(2^2 + 2^2) = 2.82842. So the closest point to the origin is (0, 2).

Example 2:

Input: points = [[0,2],[2,0],[2,2]], k = 2

Output: [[0,2],[2,0]]
Explanation: The output [2,0],[0,2] would also be accepted.

Constraints:

1 <= k <= points.length <= 1000
-100 <= points[i][0], points[i][1] <= 100

*/

class Solution_0 {
public:
    // compute, them sort then loop the first k
    // time O(NlogN) space O(N)

    // better solution is using a maxHeap: keep only k elements
    // time O(Nlogk) space O(k)
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        using Index = int;
        using Distance = int;
        using PointDistance = pair<Distance, Index>;
        auto smaller = [](const PointDistance& l, const PointDistance& r){
            return l.first<=r.first;
        };
        std::priority_queue<PointDistance, std::vector<PointDistance>, decltype(smaller)> maxHeap(smaller);
        for(int i=0; i<points.size(); ++i){
            const auto & point = points[i];
            const int distance = point[0]*point[0] + point[1]*point[1];
            maxHeap.push({distance, i});
            if(maxHeap.size() > k) maxHeap.pop(); //pop max, keep smaller k
        }
        vector<vector<int>> res;
        while(!maxHeap.empty()){
            res.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }
        return res;
    }
};

//quick select
class Solution {
public:
    // compute, them sort then loop the first k
    // time O(NlogN) space O(N)

    // better solution is using a maxHeap: keep only k elements
    // time O(Nlogk) space O(k)
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        using Index = int;
        using Distance = int;
        using PointDistance = pair<Distance, Index>;
        auto smaller = [](const PointDistance& l, const PointDistance& r){
            return l.first<=r.first;
        };
        std::priority_queue<PointDistance, std::vector<PointDistance>, decltype(smaller)> maxHeap(smaller);
        for(int i=0; i<points.size(); ++i){
            const auto & point = points[i];
            const int distance = point[0]*point[0] + point[1]*point[1];
            maxHeap.push({distance, i});
            if(maxHeap.size() > k) maxHeap.pop(); //pop max, keep smaller k
        }
        vector<vector<int>> res;
        while(!maxHeap.empty()){
            res.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }
        return res;
    }
};

class Solution_quick_select {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int L = 0, R = points.size() - 1;
        int pivot = -1;

        while (pivot != k) {// pivot makes sure all left elements are smaller, when it's k, we find all the k min elements
            pivot = partition(points, L, R);// Partition is making sure [smaller , pivot, biger]
            if (pivot < k) { 
                L = pivot + 1;// this pivot doesn't offer us less than k elements, so we move to the right side to do the partition
            } else {
                R = pivot - 1;//this pivot gave use more than k elements, so we move to the left
            }
        }
        return vector<std::vector<int>>(points.begin(), points.begin() + k);
    }

private:
    /*
    Partition example with distances: [100, 90, 50, 9, 12, 10, 25, 13, 61]
    
    Choose pivot = 61 (rightmost element at index 8)
    i = 0 (boundary of elements ≤ pivot)
    Scan j from 0 to 7:
    
    j=0: dist=100 > 61  → skip, i=0
         [100, 90, 50, 9, 12, 10, 25, 13 | 61]
                                           ^pivot
    j=1: dist=90 > 61   → skip, i=0
    j=2: dist=50 ≤ 61   → swap(arr[0], arr[2]), i=1
         [50, 90, 100, 9, 12, 10, 25, 13 | 61]
          ^i
    j=3: dist=9 ≤ 61    → swap(arr[1], arr[3]), i=2
         [50, 9, 100, 90, 12, 10, 25, 13 | 61]
              ^i
    j=4: dist=12 ≤ 61   → swap(arr[2], arr[4]), i=3
         [50, 9, 12, 90, 100, 10, 25, 13 | 61]
                  ^i
    j=5: dist=10 ≤ 61   → swap(arr[3], arr[5]), i=4
         [50, 9, 12, 10, 100, 90, 25, 13 | 61]
                     ^i
    j=6: dist=25 ≤ 61   → swap(arr[4], arr[6]), i=5
         [50, 9, 12, 10, 25, 90, 100, 13 | 61]
                         ^i
    j=7: dist=13 ≤ 61   → swap(arr[5], arr[7]), i=6
         [50, 9, 12, 10, 25, 13, 100, 90 | 61]
                             ^i
    
    Final: swap(arr[6], arr[8]) to place pivot in correct position
         [50, 9, 12, 10, 25, 13, 61, 90, 100]
                                 ^pivot at index 6
    
    All elements left of index 6 are ≤61, all right are >61
    Return 6
    */
    int partition(vector<vector<int>>& points, int l, int r) {
        int pivotIdx = r;
        int pivotDist = euclidean(points[pivotIdx]);
        int notSorted = l; // Before this one, all is smaller than pivot
        for (int j = l; j < r; j++) {
            if (euclidean(points[j]) <= pivotDist) {
                swap(points[notSorted], points[j]);
                notSorted++;
            }
        }
        swap(points[notSorted], points[r]);
        return notSorted;
    }

    int euclidean(const vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }
};
