/*
Interleaving String
Medium
Topics
Company Tags
Hints
You are given three strings s1, s2, and s3. Return true if s3 is formed by interleaving s1 and s2 together or false otherwise.

Interleaving two strings s and t is done by dividing s and t into n and m substrings respectively, where the following conditions are met

|n - m| <= 1, i.e. the difference between the number of substrings of s and t is at most 1.
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
Interleaving s and t is s1 + t1 + s2 + t2 + ... or t1 + s1 + t2 + s2 + ...
You may assume that s1, s2 and s3 consist of lowercase English letters.

Example 1:
Input: s1 = "aaaa", s2 = "bbbb", s3 = "aabbbbaa"

Output: true
Explanation: We can split s1 into ["aa", "aa"], s2 can remain as "bbbb" and s3 is formed by interleaving ["aa", "aa"] and "bbbb".

Example 2:

Input: s1 = "", s2 = "", s3 = ""

Output: true
Example 3:

Input: s1 = "abc", s2 = "xyz", s3 = "abxzcy"

Output: false
Explanation: We can't split s3 into ["ab", "xz", "cy"] as the order of characters is not maintained.
*/


/*

ideas: 
    s, t, s, t or t, s, t, s

    put two pointers on s1, s2, compare s3 to the s1 and s2, match the first substring from s1 or s2
    then recursive
    if more choince: anyof the recursion returns true is true
*/
class Solution {
private:
    bool isInterleave(const string& s1, const string& s2, const string& s3,
    int p1, int p2, vector<vector<int>>& memory){
        int p3 = p1+p2;
        if(p3 == s3.size()) return p1==s1.size() && p2 ==s2.size();

        auto& cache = memory[p1][p2];
        if(cache != -1) return cache;
        
        return cache = 
              (s3[p3] == s1[p1] && p1<s1.size() && isInterleave(s1, s2, s3, p1+1, p2, memory))
            ||(s3[p3] == s2[p2] && p2<s2.size() && isInterleave(s1, s2, s3, p1, p2+1, memory));
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        vector<vector<int>> memory(s1.size()+1, vector<int>(s2.size()+1, -1));
        // we could have p1 = size1 and p2 = 0 1, 2... so we need to have one more in the memory

        return isInterleave(s1, s2, s3, 0, 0, memory);
    }
};
