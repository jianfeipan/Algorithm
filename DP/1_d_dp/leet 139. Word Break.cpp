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
    vector<int> memory;
    size_t max_word_len;

    bool dfs(int from, const string& s, const unordered_set<string>& words){
        if(from == s.size()) return true;

        auto& cache = memory[from];
        if(cache!=-1) return cache;

        for(int len = 1; len+from <= s.size() && len <=max_word_len; ++len){
            if(words.count(s.substr(from, len)) && dfs(from+len, s, words)) return cache = true;
        }
        return cache = false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        memory = vector<int>(s.size(), -1);
        max_word_len = 0;
        for(const auto& word:wordDict) max_word_len = max(max_word_len, word.size());

        unordered_set<string> words(wordDict.begin(), wordDict.end());
        return dfs(0, s, words);
    }
};

