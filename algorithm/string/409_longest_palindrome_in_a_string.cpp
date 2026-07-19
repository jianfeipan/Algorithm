 /*
 Given a string s, return the longest substring of s that is a palindrome.

A palindrome is a string that reads the same forward and backward.

If there are multiple palindromic substrings that have the same length, return any one of them.

Example 1:

Input: s = "ababd"

Output: "bab"
Explanation: Both "aba" and "bab" are valid answers.

Example 2:

Input: s = "abbc"

Output: "bb"
Constraints:

1 <= s.length <= 1000
s contains only digits and English letters.

 
 */   

/*
idea: 
    start from every letter, to to the right, until it's nomore a palindrome, 
    update the max length then to next letter. 
    O(n^3)
     V
    "ababdbab"

improvement: 
    where do we have duplications: 
        ->the palindrome comparason
    how can we avoid that:
        ->isPalindrome[from][to] = -1(not computed), 0(no) ,1(yes)
    O(n^2)
*/

class Solution_bf_cache {
private:
    bool isPalindrome(const string& s, 
                    int from, int to, 
                    vector<vector<int>>& cache){
        
        if(cache[from][to] != -1) return cache[from][to];

        while(from<to){
            if(s[from] != s[to]) {
                cache[from][to] = 0;
                return false;
            }
            ++from;
            --to;
        }
        cache[from][to] = 1;
        return true;
    }

public:
    string longestPalindrome(string s) {
        vector<vector<int>> cache(s.size(), vector<int>(s.size(), -1));

        string longest{s[0]};
        for(int from=0; from<s.size(); ++from){
            for(int to=from+1; to<s.size();++to){
                if(isPalindrome(s, from, to, cache)){
                    const auto len=to-from+1;
                    if(longest.size() < len){
                        longest = s.substr(from, len);
                    }
                }
            }
        }
        return longest;
    }
};

class Solution {
/*
idea: 
    every palindrome string is extend from one letter or two identical letters

    go over letters  one by one,  extend from there and see how far it goes
    O(n^2)
*/
public:
    string longestPalindrome(string s) {
        int maxFrom = 0;
        int maxLen = 1;
        for(int i=0; i<s.size(); ++i){
            // extend from 1 letter
            int l = i-1;
            int r = i+1;
            while(l>=0 && r<s.size()){
                if(s[l]==s[r]){
                    const auto len = r-l+1;
                    if(len>maxLen){
                        maxLen = len;
                        maxFrom = l;
                    }
                }else{
                    break;
                }
                --l;
                ++r;
            }

            // start from two letters
            l=i;
            r=i+1;
            while(l>=0 && r<s.size()){
                if(s[l]==s[r]){
                    const auto len = r-l+1;
                    if(len>maxLen){
                        maxLen = len;
                        maxFrom = l;
                    }
                }
                else {
                    break;
                }
                --l;
                ++r;
            }
        }
        return s.substr(maxFrom, maxLen);
    }
};

