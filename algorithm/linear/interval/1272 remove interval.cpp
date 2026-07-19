#include <iostream>
#include <vector>
#include <algorithm>
/*
The goal is to take a sorted list of non-overlapping intervals and a toBeRemoved interval. 
  You need to 
    - remove the overlapping portion of any interval that intersects with toBeRemoved 
    - and return a new list of sorted, non-overlapping intervals.
*/
using namespace std;

class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> result;
        int removeStart = toBeRemoved[0];
        int removeEnd = toBeRemoved[1];

        for (const auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];

            // Scenario 1 & 2: No overlap
            if (end <= removeStart || start >= removeEnd) {
                result.push_back({start, end});
            } 
            // Scenario 3: Overlap exists
            else {
                // Check if there is a part to the left of the removal zone
                if (start < removeStart) {
                    result.push_back({start, removeStart});
                }
                // Check if there is a part to the right of the removal zone
                if (end > removeEnd) {
                    result.push_back({removeEnd, end});
                }
            }
        }
        return result;
    }
};

// --- Test Helper Function ---
void printIntervals(const vector<vector<int>>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); ++i) {
        cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
        if (i < intervals.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Test Case 1
    vector<vector<int>> intervals1 = {{0, 2}, {3, 4}, {5, 7}};
    vector<int> remove1 = {1, 6};
    // Expected: [[0,1],[6,7]]
    auto res1 = sol.removeInterval(intervals1, remove1);
    cout << "Test 1: ";
    printIntervals(res1);

    // Test Case 2
    vector<vector<int>> intervals2 = {{0, 5}};
    vector<int> remove2 = {2, 3};
    // Expected: [[0,2],[3,5]]
    auto res2 = sol.removeInterval(intervals2, remove2);
    cout << "Test 2: ";
    printIntervals(res2);

    // Test Case 3
    vector<vector<int>> intervals3 = {{-5, -4}, {-3, -2}, {1, 2}, {3, 5}, {8, 9}};
    vector<int> remove3 = {-1, 4};
    // Expected: [[-5,-4],[-3,-2],[4,5],[8,9]]
    auto res3 = sol.removeInterval(intervals3, remove3);
    cout << "Test 3: ";
    printIntervals(res3);

    return 0;
}
