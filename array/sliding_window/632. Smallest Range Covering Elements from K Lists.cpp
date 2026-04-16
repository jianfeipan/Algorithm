/*You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.



Example 1:

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Example 2:

Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]
 */

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <cassert>
using namespace std;

class Solution {

  // k way merge: with number and which list they belongs to
  // sliding window, find a left, right where we have k distint element
  //   -> left right, hashmap count
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        const auto k = nums.size();
        // k way merge:
        using Num = int;
        using Q = int;
        using Node = pair<Num, Q>;
        vector<Node> sorted;

        using Index = int;
        vector<Index> head(k);

        priority_queue<Node, vector<Node>, greater<Node>> minHeap;

        auto pushNext = [&](Q q) {
            auto& currentHeadIndex = head[q];
            auto& queue = nums[q];
            if(currentHeadIndex < queue.size()){
                minHeap.push({queue[currentHeadIndex], q});
                ++currentHeadIndex;
            }
        };

        for(Q q=0; q<k; ++q){
            pushNext(q);
        }

        while(!minHeap.empty()){
            auto [num, q] = minHeap.top();
            minHeap.pop();
            sorted.emplace_back(num, q);
            pushNext(q);
        }
        // sliding window to count distinct Q
        unordered_map<Q, int> count;
        int l = 0;
        int r = 0;

        int minLen = INT_MAX;
        vector<int> minRes;
        while(r<sorted.size()){
            const auto& [rightNum, rightQ] = sorted[r];
            ++count[rightQ];
            while(count.size() == k){
                auto& [leftNum, leftQ] = sorted[l];
                auto currentLen = rightNum - leftNum + 1;
                if(currentLen < minLen){
                    minLen = currentLen;
                    minRes = {leftNum, rightNum};
                }
                --count[leftQ];
                if(count[leftQ] == 0) count.erase(leftQ);
                ++l;
            }
            ++r;
        }
        return minRes;
    }
};

int main() {
    Solution sol;

    // Test 1: LeetCode example - nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
    // Expected: [20, 24]
    {
        vector<vector<int>> nums = {{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
        auto res = sol.smallestRange(nums);
        cout << "Test 1: [" << res[0] << ", " << res[1] << "]" << endl;
        assert(res[0] == 20 && res[1] == 24);
    }

    // Test 2: Single element lists - nums = [[1],[2],[3]]
    // Expected: [1, 3]
    {
        vector<vector<int>> nums = {{1},{2},{3}};
        auto res = sol.smallestRange(nums);
        cout << "Test 2: [" << res[0] << ", " << res[1] << "]" << endl;
        assert(res[0] == 1 && res[1] == 3);
    }

    // Test 3: Overlapping lists - nums = [[1,2,3],[1,2,3],[1,2,3]]
    // Expected: [1, 1]
    {
        vector<vector<int>> nums = {{1,2,3},{1,2,3},{1,2,3}};
        auto res = sol.smallestRange(nums);
        cout << "Test 3: [" << res[0] << ", " << res[1] << "]" << endl;
        assert(res[0] == 1 && res[1] == 1);
    }

    cout << "All tests passed!" << endl;
    return 0;
}
