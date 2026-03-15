/*Palindromic Substrings

Given a string s, return the number of substrings within s that are palindromes.

A palindrome is a string that reads the same forward and backward.

Example 1:

Input: s = "abc"

Output: 3
Explanation: "a", "b", "c".

Example 2:

Input: s = "aaa"

Output: 6
Explanation: "a", "a", "a", "aa", "aa", "aaa". Note that different substrings are counted as different palindromes even if the string contents are the same.

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.*/

/*
idea: 
    from each letter, we go extend to left and right, make sure it's same and extend
    every extend is a new substring with palindrome
    from two same letters, do the same

    O(n^2)
*/

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        auto extend = [&s, &count](int l, int r){
            while(l>=0 && r<s.size()){
                if(s[l]==s[r]){
                    ++count;
                }else{
                    break;
                }
                --l;
                ++r;
            }
        };

        for(int i=0; i<s.size(); ++i){
            // start from one letter
            extend(i,i);
            // start from two letters
            extend(i,i+1);
        }

        return count;
    }
};
