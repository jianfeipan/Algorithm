
/*
890. Find and Replace Pattern
Medium
3.7K
166
Companies
Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.

A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.

Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.

 

Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
Example 2:

Input: words = ["a","b","c"], pattern = "a"
Output: ["a","b","c"]
 


*/
class Solution 
{
/*
fact:
     abb and mee are the same, --> what is a pattern? -->abb just means first  is different from second, and second is same as third
idea:
    pattern can be represent to a map of set of index: [a[0] b[1,2]] there are two different letters, fist is just on 0, and second is 1,2 
    so when to match, you need to verify : 
        1 a != b --> str[0] != str[1] 
        2 str[1] == str[2]

*/

private:
    bool match(const unordered_map<char, vector<int>> &patternMap, const string & word)
    {
        array<bool, 26> bigMap{};
        //a!=b
        for(const auto & [_, indexes]: patternMap)
        {
            if(bigMap[word[indexes.front()]-'a']) 
                return false;
            else
              bigMap[word[indexes.front()]-'a'] = true;  
            
        }


        for(const auto & [_, indexes]: patternMap)
        {
            const char & key = word[indexes.front()];
            for(const auto & sameIndex : indexes)
            {
                if(key!=word[sameIndex]) return false;
            }
        }

        return true;
    }

public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) 
    {
        unordered_map<char, vector<int>> patternMap;
        for(int i=0; i<pattern.size(); ++i)
        {
            patternMap[pattern[i]].push_back(i);
        }

        vector<string> res;
        for(const auto & word : words)
        {
            if(pattern.size() == word.size() && match(patternMap, word))
            {
                res.push_back(word);
            }
        }

        return res;
    }
};
