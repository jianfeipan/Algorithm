class Solution {
private:
    vector<vector<int>> memory;

    bool is_inter_leave_from(int index1, int index2, 
                            const string& s1, 
                            const string& s2, 
                            const string& s3) {
        if(index1 == s1.size() && index2 == s2.size()) return true;

        auto& cache = memory[index1][index2];
        if(cache!=-1) return cache;

        const auto target = s3[index1 + index2];
        if(index1<s1.size() && s1[index1] == target && is_inter_leave_from(index1+1, index2, s1, s2, s3)) 
            return cache = true;
        
        if(index2<s2.size() && s2[index2] == target && is_inter_leave_from(index1, index2+1, s1, s2, s3)) 
            return cache = true;

        return cache = false;
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;

        memory = vector<vector<int>>(s1.size()+1, vector<int>(s2.size()+1, -1));

        return is_inter_leave_from(0, 0, s1, s2, s3);
    }
};

/*
Interleaving String
Medium Topics Company Tags
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

Output: false*/