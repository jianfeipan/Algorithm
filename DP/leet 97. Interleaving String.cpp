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
    bool dfs(const string& s1, const string& s2, const string& s3,
            int i1, int i2, int i3, vector<vector<int>>& memory){

        cout<< i1 << " - " << i2<< " - "<<i3<<endl;
        /*
          i
        aaaa
            i
        bbbb
              i
        aabbbbaa
        
        */

        if(i3==s3.size()) return i1==s1.size() && i2==s2.size();

        if(memory[i1][i2]!= -1) return memory[i1][i2];

        {// try s1
            int current1 = i1;
            int current3 = i3;
            while(current1<s1.size() && s1[current1] == s3[current3]){
                ++current1;
                ++current3;
            }
            if(current1>i1) 
                if(dfs(s1,s2,s3, current1, i2, current3, memory)) 
                    return memory[i1][i2] = true;
        }
        {//try s2

            int current2 = i2;
            int current3 = i3;
            while(current2<s2.size() && s2[current2] == s3[current3]){
                ++current2;
                ++current3;
            }
            if(current2>i2) 
                if(dfs(s1, s2, s3, i1, current2, current3, memory)) 
                    return memory[i1][i2] = true;
        }
        return memory[i1][i2]=false;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        vector<vector<int>> memory(s1.size()+1, vector<int>(s2.size()+1, -1));
        return dfs(s1, s2, s3, 0 ,0, 0, memory);
    }
};
