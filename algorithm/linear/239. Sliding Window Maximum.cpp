/*
You are given an array of integers nums and an integer k. There is a sliding window of size k that starts at the left edge of the array. The window slides one position to the right until it reaches the right edge of the array.

Return a list that contains the maximum element in the window at each step.

Example 1:

Input: nums = [1,2,1,0,4,2,6], k = 3

Output: [2,2,4,4,6]

Explanation: 
Window position            Max
---------------           -----
[1  2  1] 0  4  2  6        2
 1 [2  1  0] 4  2  6        2
 1  2 [1  0  4] 2  6        4
 1  2  1 [0  4  2] 6        4
 1  2  1  0 [4  2  6]       6
Constraints:

1 <= nums.length <= 1000
-10,000 <= nums[i] <= 10,000
1 <= k <= nums.length
*/

class Solution_multiset {
/*
ideas:
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
BF: O(n*k)
 when I move window: using a multi-set to keep order of K elements, update it and get max
 O(nlogK)
*/
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> windowMax;windowMax.reserve(nums.size()-k+1);
        multiset<int> ordered;
        for(int i=0; i<k; ++i){
            ordered.insert(nums[i]);
        }
        windowMax.push_back(*ordered.rbegin());

        for(int i=1; i+k-1<nums.size(); ++i){
            ordered.erase(ordered.find(nums[i-1]));
            ordered.insert(nums[i+k-1]);
            
            windowMax.push_back(*ordered.rbegin());
        }
        return windowMax;
    }
};


// O(N) is possible with monotonic deque:

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; // Stores indices, keep max index in front

        for (int i = 0; i < nums.size(); ++i) {
            // 1. Remove indices of elements smaller than the current element
            // because they will never be the maximum in any future window.
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);

            // 2. Remove the front index if it has fallen out of the window
            if (dq.front() == i - k) {
                dq.pop_front();
            }

            // 3. The front of the deque is the maximum for the current window
            // (Only start adding to results once we've reached the first full window)
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};
