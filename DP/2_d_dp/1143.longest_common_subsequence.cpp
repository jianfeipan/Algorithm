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
    vector<vector<int>> memory;

    int dfs(const string& s1, const string& s2, int index1, int index2){
        if(index1 == s1.size() || index2 == s2.size()) return 0;

        auto& cache = memory[index1][index2];
        if(cache != -1) return cache;

        if(s1[index1] == s2[index2]) return cache=(1 + dfs(s1, s2, index1+1, index2+1));
        else return cache = max(dfs(s1, s2, index1+1, index2), dfs(s1, s2, index1, index2+1));
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        memory = vector<vector<int>>(text1.size(), vector<int>(text2.size(), -1));
        return dfs(text1, text2, 0, 0);
    }
};
