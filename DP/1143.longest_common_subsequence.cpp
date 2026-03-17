/*
Longest Common Subsequence

Given two strings text1 and text2, return the length of the longest common subsequence between the two strings if one exists, otherwise return 0.

A subsequence is a sequence that can be derived from the given sequence by deleting some or no elements without changing the relative order of the remaining characters.

For example, "cat" is a subsequence of "crabt".
A common subsequence of two strings is a subsequence that exists in both strings.

Example 1:

Input: text1 = "cat", text2 = "crabt" 

Output: 3 
Explanation: The longest common subsequence is "cat" which has a length of 3.

Example 2:

Input: text1 = "abcd", text2 = "abcd"

Output: 4
Example 3:

Input: text1 = "abcd", text2 = "efgh"

Output: 0
Constraints:

1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.
*/

/*
idea:
             i              j
    text1 = "cat", text2 = "crabt"
    c=c :1
    at, rabt 

    1. compare the first letter, then recusion
        -> same: 1 + recusion to next position
        -> different: max of move first one or move second one   
        -> Boudry: one of the pointer t the end: return 0
        -> cache: top-down solution to reduce computation: two dimension


*/

class Solution {
private:
    int _subsequenceLenth(const string& s1, const string& s2, 
                          int s1Idx, int s2Idx, vector<vector<int>>& dp){
        if(s1Idx==s1.size() || s2Idx==s2.size()){
            return 0;
        }

        auto& cache = dp[s1Idx][s2Idx];
        if(cache!=-1){
            return cache;
        }

        if(s1[s1Idx] == s2[s2Idx])
            return  cache = (1+ _subsequenceLenth(s1, s2, s1Idx+1, s2Idx+1, dp));

        return cache = max(
            _subsequenceLenth(s1, s2, s1Idx+1, s2Idx, dp),
            _subsequenceLenth(s1, s2, s1Idx, s2Idx+1, dp)
        );
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        const auto& len1 = text1.size();
        const auto& len2 = text2.size();
        vector<vector<int>> dp(len1, vector<int>(len2, -1));

        return _subsequenceLenth(text1, text2, 0, 0, dp);
    }
};
