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
    BF: look at all substrings O(N^3) check palindromic

    palindromic-> every letter extends to left and right: O(n^2)
                or every two letters extend

*/
class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        // extend from one letter
        for(int i=0; i<s.size(); ++i){
            int l=i;
            int r=i;
            while(l>=0 && r<s.size() && s[l] == s[r]){
                    ++count;
                    --l;
                    ++r;
            }
        }

        //extend from two letters
        for(int i=0; i<s.size()-1; ++i){
            int l=i;
            int r=i+1;
            while(l>=0 && r<s.size() && s[l] == s[r]){
                ++count;
                --l;
                ++r;
            }
        }

        return count;
    }
};