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


[""]
["a"]
["",""]
["eat","tea","tan","ate","nat","bat"]
  
  
  
  */
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        //Idea1 : sort all strings, use a map <sorted string, set<originalStrings>> to group
        
        vector<string> sortedStrs(strs);
        for_each(sortedStrs.begin(), sortedStrs.end(), [](string& str){
            sort(str.begin(), str.end());
        });
        
        map<string, vector<string>> groupStrs;
        for(size_t i = 0; i < sortedStrs.size(); ++i)
        {
            groupStrs[sortedStrs[i]].push_back(strs[i]);
        }
        
        vector<vector<string>> result;
        result.reserve(groupStrs.size());
        
        for(const auto & strPair : groupStrs)
        {
            result.push_back(strPair.second);
        }
                             
        return result;
    }
};
