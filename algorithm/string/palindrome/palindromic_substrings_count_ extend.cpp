/*
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

 

Example 1:

Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:

Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.
*/


/*
idea:
    palindromic-> every letter extends to left and right: O(n^2)
                or every two letters extend

*/

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;

        auto extend = [&](int l, int r, const string& s){
            if(0<=l && r<s.size()){
                while(0<=l && r<s.size() && s[l] == s[r]) {
                    ++count; // every time we extend successfully, it's a new substring
                    --l; ++r;
                }
            }
        };
        
        // from one letter
        for(int i=0; i<s.size(); ++i) extend(i, i,  s);
        // from two letters
        for(int i=0; i<s.size(); ++i) extend(i, i+1,  s);

        return count;
    }
};
