/*
Split Array Largest Sum

You are given an integer array nums and an integer k, split nums into k non-empty subarrays
such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A subarray is a contiguous part of the array.

Example 1:

Input: nums = [2,4,10,1,5], k = 2

Output: 16


Input: nums = [1,0,2,3,5], k = 4

Output: 5


*/

/*
DP
splitArray ([0, n-1], k)
    take [0] splitArray[1, n-1], k-1
    or
    take[0, 1] splitArray[2, n-1], k-1
    ...
    return the min
complexity: you have K "|" put them to N places N*(N-1)*..*(N-K)
with memory: every from * k i only go once: O(N*K)

**Time Complexity:** $O(N^2 \cdot K)$

- There are $O(N \cdot K)$ unique subproblems (memoization states: `from` × `k`).
- Each subproblem runs a `for` loop that iterates up to $O(N)$ times.
- So total: $O(N^2 \cdot K)$.

**Space Complexity:** $O(N \cdot K)$

- The memoization table is $N \times (K+1)$.
- Recursion stack depth is at most $K$.

k=4
0 1 2 3 4
1 0 2 3 5

from0 k =4:
1 0 2 3 5
    from 1 k = 3
    1 | 0 2 3 5
        from 2 k = 2
        1 | 0 | 2 3 5
            from 3 k=1
                1|0|2|3 5 ->8
        from 3 k = 2
        1|0 2| 3 5 -> 5
    from 2 k =3
    1 0 | 2 3 5 -> 5


*/
#include <numeric>
class Solution {
private:
    int splitFrom(vector<int>& nums, int from, int k, vector<vector<int>>& memory){
        if(k==1) return accumulate(nums.begin()+from, nums.end(), 0);
        if(nums.size() - from == k) return *max_element(nums.begin()+from, nums.end());
        //[0 1 2 3 4] from 2 k=3: single numbers

        auto& cache = memory[from][k];
        if(cache != -1) return cache;

        int minSum = INT_MAX;
        int sum = 0;
        for(int i = from; i<=nums.size()-k; ++i){
            sum+=nums[i];
            minSum = min(minSum,
                         max(sum, splitFrom(nums, i+1, k-1, memory)));
        }
        return cache = minSum;
    }
public:
    int splitArray(vector<int>& nums, int k) {
        vector<vector<int>> memory(nums.size(), vector<int>(k+1, -1));
        return splitFrom(nums, 0, k, memory);
    }
};
