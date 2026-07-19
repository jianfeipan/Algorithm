/*
Max team size with a core interval

Given n people, each with a skill interval [start_i, end_i],
find the maximum team size such that the intersection of all
team members' intervals is non-empty (i.e., there exists a
"core interval" common to all chosen members).

Approach:
  Sort intervals by start. For each interval i, its start is
  the latest left endpoint among intervals [0..i]. We need all
  chosen intervals to have end >= start_i. So we want the max
  number of intervals from [0..i] whose end >= intervals[i].start.

  Equivalently: sort by start, then for position i, count how
  many intervals in [0..i] have end >= intervals[i].start.
  This can be done with a multiset or sorting + binary search.

  Better approach: Sort by start. Use a min-heap of ends. For each
  interval, push its end. Pop all ends < current start. The heap
  size is the current team size. Track the max.

  Time: O(n log n), Space: O(n)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Returns the maximum team size such that all members share a common point
int maxTeamSize(vector<pair<int,int>>& intervals) {
    if (intervals.empty()) return 0;

    // Sort by start time
    sort(intervals.begin(), intervals.end());

    // Min-heap of end times
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int maxSize = 0;

    for (auto& [start, end] : intervals) {
        // Remove intervals whose end < current start (no overlap)
        while (!minHeap.empty() && minHeap.top() < start) {
            minHeap.pop();
        }
        minHeap.push(end);
        maxSize = max(maxSize, (int)minHeap.size());
    }

    return maxSize;
}

// Variant: given a fixed core interval [L, R], find max team size
// whose intersection still contains [L, R].
// A member [s, e] qualifies iff s <= L and e >= R.
int maxTeamSizeWithCore(vector<pair<int,int>>& intervals, int L, int R) {
    int count = 0;
    for (auto& [s, e] : intervals) {
        if (s <= L && e >= R) count++;
    }
    return count;
}

int main() {
    // Example 1: find max team with any common core
    vector<pair<int,int>> intervals = {{1,5}, {2,6}, {3,7}, {4,8}, {6,10}};
    cout << "Max team size (common overlap): " << maxTeamSize(intervals) << endl;
    // intervals sorted: {1,5},{2,6},{3,7},{4,8},{6,10}
    // At {4,8}: heap has ends {5,6,7,8}, all >= 4 → size 4
    // At {6,10}: pop 5, heap = {6,7,8,10} → size 4
    // Answer: 4

    // Example 2: fixed core [3, 5]
    vector<pair<int,int>> intervals2 = {{1,5}, {2,6}, {3,7}, {4,8}, {6,10}};
    cout << "Max team with core [3,5]: " << maxTeamSizeWithCore(intervals2, 3, 5) << endl;
    // {1,5}: 1<=3 && 5>=5 ✓
    // {2,6}: 2<=3 && 6>=5 ✓
    // {3,7}: 3<=3 && 7>=5 ✓
    // {4,8}: 4>3 ✗
    // {6,10}: 6>3 ✗
    // Answer: 3

    return 0;
}
