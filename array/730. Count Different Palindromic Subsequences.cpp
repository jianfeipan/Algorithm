class Solution {
/*
730. Count Different Palindromic Subsequences
Solved
Hard
Topics
premium lock icon
Companies
Hint
Given a string s, return the number of different non-empty palindromic subsequences in s. Since the answer may be very large, return it modulo 109 + 7.

A subsequence of a string is obtained by deleting zero or more characters from the string.

A sequence is palindromic if it is equal to the sequence reversed.

Two sequences a1, a2, ... and b1, b2, ... are different if there is some i for which ai != bi.

 

Example 1:

Input: s = "bccb"
Output: 6
Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
Example 2:

Input: s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"
Output: 104860361
Explanation: There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 109 + 7.
 

Constraints:

1 <= s.length <= 1000
s[i] is either 'a', 'b', 'c', or 'd'.
s = "bccb"
b
c
bb
cc
bcb
bccb


s[i] is either 'a', 'b', 'c', or 'd'.
dp[i][j] -> max palindromic subsequences from i to j


*/

public:
    constexpr static int MOD = 1e9 + 7;
    int countPalindromicSubsequences(string s) {
        const int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,0));

        for(int i = 0; i < n; i++) dp[i][i] = 1; //every single char is palindromic
        
        for(int len = 2; len<=n; ++len){
            for(int i = 0; i<=n-len; ++i){
                int j= i+len-1;
                if(s[i] != s[j]){
                    // i   j
                    // abccb
                    dp[i][j] = ((dp[i+1][j] + dp[i][j-1]) % MOD - dp[i+1][j-1] + MOD) % MOD;
                }else{
                    // i   j
                    // aabca
                    int low = i + 1, high = j - 1;

                    while (low <= high && s[low] != s[i]) low++;
                    while (low <= high && s[high] != s[j]) high--;
                    
                    if (low > high) {
                        // abcda -> between a, there is no a: for every palindromic
                        // [i+1, j-1], the the left a and right a, 
                        // they are still palindromic(*2), 
                        // and the two as: wille give aa a so (+2)
                        dp[i][j] = (dp[i+1][j-1] * 2 + 2) % MOD;
                    } else if (low == high) {
                        // low == high means there is only one a inside [i+1, j-1]
                        // a|abc|a : since there is duplication, dp[abc] = 3
                        // dp[aabca] = dp[abc]+  a|dp[abc]|a  (*2)
                        // + aa a -> the single a is already in dp[abc] so we do (+1)
                        dp[i][j] = (dp[i+1][j-1] * 2 + 1) % MOD;
                    } else {
                        // low < high means there isat least 2 a inside [i+1, j-1]
                        //  a  abca  a
                        // a| abca |a : since there is duplication 
                        // dp[i+1][j-1] * 2 - dp[low+1][high-1]
                        dp[i][j] = ((dp[i+1][j-1] * 2 - dp[low+1][high-1]) % MOD + MOD) % MOD;
                    }


                }

            }
        }
        return dp[0][n-1];


    }
};
