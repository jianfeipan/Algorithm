/*
Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

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
    bool _wordBreak(const string& s, 
                    const unordered_set<string>& dict,
                    int from, 
                    vector<string>& sentences, 
                    string path,
                    vector<int>& dp){
        // don't read dp or write dp here: we always the final state to write different answers.
        if(from == s.size()){
            // we reached end, used all string s, push this path to the final result
            // drop the first space
            sentences.push_back(path.substr(1, path.size()-1));
            return true; // use this info to pruning no result branches
        }

        if(dp[from] == 0) return false;// if we already know there is no solution for 'from' just do nothing
        
        for(int i=from; i<s.size(); ++i){//TODO: max word size in Dict could reduce the loop
            int len = i-from+1;
            const auto current = s.substr(from, len);
            if(dict.count(current)){
                if(_wordBreak(s, dict, i+1, sentences, path+" "+current, dp))
                {
                    dp[from] = 1;
                }
            }
        }
        return dp[from];
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict{wordDict.begin(), wordDict.end()};
        vector<string> sentences;
        vector<int> dp(s.size(), -1);

        _wordBreak(s, dict, 0, sentences, "", dp);
        return sentences;
    }
};
