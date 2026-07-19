/*
Maximize alternating-sum over four array partitions:
Given an integer array arr[1..n] (1-based).
 Choose indices a, b, c with 1 ≤ a ≤ b ≤ c ≤ n+1. For any half-open interval [l, r),
 define sum[l, r) as the sum of arr[l..r−1], with sum[l, l) = 0.
 Cutting at a, b, c partitions the array into four contiguous segments in order:
  S4 = sum[1, a), S1 = sum[a, b), S2 = sum[b, c), S3 = sum[c, n+ 1).
  Define grossValue(a, b, c) = S1 − S2 + S3 − S4.
  Compute the maximum possible grossValue over all valid (a, b, c).
  State your algorithm and its time/space complexity;
   handle edge cases where cuts coincide or lie at the ends.

Algorithm:
  grossValue = S1 - S2 + S3 - S4
  Using prefix sums P[0..n] (P[0]=0, P[i]=arr[1]+...+arr[i]):
    S4=P[a-1], S1=P[b-1]-P[a-1], S2=P[c-1]-P[b-1], S3=P[n]-P[c-1]
    grossValue = -2*P[a-1] + 2*P[b-1] - 2*P[c-1] + P[n]

  Let A=a-1, B=b-1, C=c-1 with 0 <= A <= B <= C <= n.
  Maximize: -P[A] + P[B] - P[C]  (factor of 2 and +P[n] are constant scaling/offset)

  Single-pass DP tracking three running maxima (left to right over i=0..n):
    best1 = max(-P[i])            -- best choice for A so far
    best2 = max(P[i] + best1)     -- best (B, A) pair so far (B >= A)
    best3 = max(-P[i] + best2)    -- best (C, B, A) triple    (C >= B >= A)

  Answer = 2 * best3 + P[n].
  Time O(n), Space O(1) (beyond the prefix sum which can be computed on the fly).
*/

#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

// O(n) time, O(1) extra space
long long maxGrossValue(const vector<int>& arr) {
    int n = arr.size();
    // prefix sum computed on the fly
    long long prefix = 0;
    long long best1 = 0;          // max(-P[A]) for A in [0..i], starts with -P[0]=0
    long long best2 = LLONG_MIN;  // max(P[B] + best1) for B in [0..i]
    long long best3 = LLONG_MIN;  // max(-P[C] + best2) for C in [0..i]

    // i ranges over 0..n (n+1 prefix-sum values P[0]..P[n])
    for (int i = 0; i <= n; ++i) {
        if (i > 0) prefix += arr[i - 1];

        best1 = max(best1, -prefix);
        best2 = max(best2, prefix + best1);
        best3 = max(best3, -prefix + best2);
    }
    return 2 * best3 + prefix;   // prefix == P[n] after the loop
}

// Brute-force O(n^3) for verification
long long maxGrossValueBrute(const vector<int>& arr) {
    int n = arr.size();
    // build prefix sums (1-indexed: P[0]=0, P[i]=arr[0]+...+arr[i-1])
    vector<long long> P(n + 1, 0);
    for (int i = 1; i <= n; ++i) P[i] = P[i - 1] + arr[i - 1];

    long long ans = LLONG_MIN;
    // a, b, c are 1-indexed with 1 <= a <= b <= c <= n+1
    for (int a = 1; a <= n + 1; ++a) {
        for (int b = a; b <= n + 1; ++b) {
            for (int c = b; c <= n + 1; ++c) {
                long long S4 = P[a - 1];
                long long S1 = P[b - 1] - P[a - 1];
                long long S2 = P[c - 1] - P[b - 1];
                long long S3 = P[n] - P[c - 1];
                long long val = S1 - S2 + S3 - S4;
                ans = max(ans, val);
            }
        }
    }
    return ans;
}

int main() {
    // --- Stress test against brute force ---
    srand(42);
    for (int t = 0; t < 10000; ++t) {
        int n = rand() % 8 + 1;           // 1..8
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rand() % 21 - 10;  // -10..10
        long long opt = maxGrossValue(arr);
        long long brute = maxGrossValueBrute(arr);
        assert(opt == brute);
    }
    cout << "All stress tests passed.\n";

    // --- Example ---
    vector<int> arr = {1, -2, 3, -4, 5};
    cout << "arr = [1, -2, 3, -4, 5]\n";
    cout << "maxGrossValue = " << maxGrossValue(arr) << "\n";
    cout << "brute force   = " << maxGrossValueBrute(arr) << "\n";

    // Edge: single element
    cout << "\narr = [7]  => " << maxGrossValue({7}) << "\n";
    // Edge: all negative
    cout << "arr = [-3,-1,-4] => " << maxGrossValue({-3, -1, -4}) << "\n";
    // Edge: all same
    cout << "arr = [2,2,2,2]  => " << maxGrossValue({2, 2, 2, 2}) << "\n";

    return 0;
}

