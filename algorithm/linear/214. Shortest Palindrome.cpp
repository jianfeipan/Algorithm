/*
214. Shortest Palindrome
Attempted
Hard
Topics
premium lock icon
Companies
You are given a string s. You can convert s to a palindrome by adding characters in front of it.

Return the shortest palindrome you can find by performing this transformation.

 

Example 1:

Input: s = "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: s = "abcd"
Output: "dcbabcd"
 

Constraints:

0 <= s.length <= 5 * 104
s consists of lowercase English letters only.
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        int count = kmp(s, string(s.rbegin(), s.rend()));
        return string(s.rbegin(), s.rend()).substr(0, s.length() - count) + s;
    }

private:

    int kmp(const string &patt, const string &txt) {
        string newString = patt + '#' + txt;
        //abcd # dcba 
        /*
        Prefix Array (Pi Array):
The KMP algorithm constructs a prefix array (pi array) that tells us the length of the longest prefix in the original string that matches the start of the reversed string. This gives us the part of the original string that doesn't need extra characters.
        */
        vector<int> pi(newString.length(), 0);
        int i = 1, k = 0;
        while (i < newString.length()) {
            if (newString[i] == newString[k]) {
                k++;
                pi[i] = k;
                i++;
            } else {
                if (k > 0) {
                    k = pi[k - 1];
                } else {
                    pi[i] = 0;
                    i++;
                }
            }
        }
        return pi.back();
    }
};
