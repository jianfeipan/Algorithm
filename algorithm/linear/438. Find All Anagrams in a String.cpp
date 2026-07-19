class Solution {
    
    /*
    
    Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
 

Constraints:

1 <= s.length, p.length <= 3 * 104
s and p consist of lowercase English letters.


scope : 
-can p size() > s.size ? yes : nothing found
-can p be empty ? no : exception
-can p have duplicated letters ? yes-->window will be set or counter map

idea : 
- brute force : window slid and check anagram for all pssible indexes
- two pointer window, with a map counting p letters, to check if anagram


"abab"
"ab"
"cbaebabacd"
"abc"
"a"
"ab"
    
    
    */
public:
    vector<int> findAnagrams(string s, string p) {
        
        vector<int> anagrams;
        
        unordered_map<char, int> dict;
        for(auto c : p) ++dict[c];
        
        int charsToMatch = dict.size();
        size_t left = 0;
        size_t right = 0;
        while(right<s.size())
        {
            while(right<s.size() && charsToMatch>0)
            {
                if(dict.count(s[right]))
                {
                    --dict[s[right]];
                    
                    if(dict[s[right]] == 0)   --charsToMatch;
                }
                ++right;
            }
            
            while(left<s.size() && charsToMatch == 0)
            {
                if(right-left == p.size()) anagrams.push_back(left);

                if(dict.count(s[left]))
                {
                    ++dict[s[left]];
                    
                    if(dict[s[left]] == 1)   ++charsToMatch;
                }
                ++left;
            }
                        
        }
        return anagrams;
    }
};
