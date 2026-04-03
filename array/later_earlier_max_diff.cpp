/*
Compute maximum later-earlier difference
Given an array, find max(arr[j] - arr[i]) where j > i.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// O(n) time, O(1) space
int maxLaterEarlierDiff(const vector<int>& arr) {
    if (arr.size() < 2) return 0;

    int minSoFar = arr[0];
    int maxDiff = INT_MIN;

    for (int i = 1; i < (int)arr.size(); ++i) {
        maxDiff = max(maxDiff, arr[i] - minSoFar);
        minSoFar = min(minSoFar, arr[i]);
    }
    return maxDiff;
}

int main() {
    vector<int> arr = {2, 3, 10, 6, 4, 8, 1};
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "Max later-earlier difference: " << maxLaterEarlierDiff(arr) << endl;
    // Expected: 10 - 2 = 8

    // Edge cases
    vector<int> decreasing = {10, 8, 5, 3, 1};
    cout << "Decreasing array: " << maxLaterEarlierDiff(decreasing) << endl;
    // Expected: -2 (8 - 10)

    vector<int> single = {42};
    cout << "Single element: " << maxLaterEarlierDiff(single) << endl;
    // Expected: 0

    return 0;
}
