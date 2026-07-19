/*
Given a string s and a dictionary of strings wordDict, 
add spaces in s to construct a sentence 
where each word is a valid dictionary word. 
Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
 

Constraints:

1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
Input is generated in a way that the length of the answer doesn't exceed 105.
*/


/*
idea:
    - move the pointer in a string to find the matched word in the dict
    - use the current match, recursively try next word in s
    - skip the current match, try to match a longer word, then recursively to next word
    - if to the end we use all s, append it to the result. 

*/
class Solution {
private:
    vector<int> memory;
    size_t max_word_len;
    vector<string> setences;

    bool dfs(int from, const string& s, stirng& setence,const unordered_set<string>& words){
        if(from == s.size()) { setences.push_back(); return true; }

        auto& cache = memory[from];
        if(cache!=-1) return cache;

        for(int len = 1; len+from <= s.size() && len <=max_word_len; ++len){
            auto cur = s.substr(from, len);
            if(words.count() && dfs(from+len, s, setence+" "+cur, words)){
                cache = true;
            } 
        }
        return cache = false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        setences.clear();
        memory = vector<int>(s.size(), -1);
        max_word_len = 0;
        for(const auto& word:wordDict) max_word_len = max(max_word_len, word.size());

        unordered_set<string> words(wordDict.begin(), wordDict.end());
        return dfs(0, s, "", words);
    }
};
