/*
Word Break
Medium
Topics
Company Tags
Hints
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of dictionary words.

You are allowed to reuse words in the dictionary an unlimited number of times. You may assume all dictionary words are unique.

Example 1:

Input: s = "neetcode", wordDict = ["neet","code"]

Output: true
Explanation: Return true because "neetcode" can be split into "neet" and "code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen","ape"]

Output: true
Explanation: Return true because "applepenapple" can be split into "apple", "pen" and "apple". Notice that we can reuse words and also not use all the words.

Example 3:

Input: s = "catsincars", wordDict = ["cats","cat","sin","in","car"]

Output: false
Constraints:

1 <= s.length <= 200
1 <= wordDict.length <= 100
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
*/

/*
idea:
    two pointers, when we find a word in dict
    -> take this as a word, and recursive on the rest
    -> dont take it continue to see if dict as a longer match , then recursive

S size = S dictionary size=D
maximum we will do S cache miss, for each it's the lengh of the string which is S
Time:
    O(S*t) t is longest words size in dictionary
space:
    O(D)

*/
class Solution {
private:
    bool _wordBreak(const string s, 
                    const unordered_set<string>& wordDict,
                    int from,
                    vector<int>& cache, 
                    int wordMaxLen){
        if(from == s.size()) return true; // reach the end of string, we find one way
        
        if(cache[from]!=-1) return cache[from];
        for(int j = from; j<s.size() && j-from+1<=wordMaxLen; ++j){
            if(wordDict.contains(s.substr(from, j-from+1))){
                if(_wordBreak(s, wordDict, j+1, cache, wordMaxLen)) {
                    cache[from]=true;
                    return true;
                }
            }
        }
        cache[from]=false;
        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict{wordDict.begin(), wordDict.end()};
        vector<int> cache(s.size(), -1);
        size_t wordMaxLen = 0;
        for(const auto& word:wordDict){
            wordMaxLen=max(wordMaxLen, word.size());
        }
        return _wordBreak(s, dict, 0, cache, wordMaxLen);
    }
};
