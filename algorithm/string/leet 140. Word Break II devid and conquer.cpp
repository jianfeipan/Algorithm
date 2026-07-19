

#include "pch.h"
#include <iostream>
#include <stack>


#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

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
*/

class Solution {
private:
    vector<string> wordBreakFrom(int from, 
                                const string& s, 
                                const unordered_set<string>& dict, 
                                unordered_map<int, vector<string>>& dp){
        if(from == s.size()) return {""};

        auto it = dp.find(from);
        if(it != dp.end()) return it->second;


        vector<string> setences;

        for(int to = from; to<s.size(); ++to){
            auto current = s.substr(from, to-from+1);
            if(dict.count(current)){
                auto nextSetences = wordBreakFrom(to+1, s, dict, dp);
                for(auto& nextSetence : nextSetences){
                    if(nextSetence.empty()) setences.push_back(current);
                    else setences.push_back(current+" "+nextSetence);
                }
            }
        }
        return dp[from] = setences;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> dp;
        return wordBreakFrom(0, s, dict, dp);
    }
};

template<typename T>
static void print(const std::vector<T> & v)
{
   std::cout << "[ ";
   for (const T & t : v)
      std::cout << t << ',  ';
   std::cout << "]" << std::endl;;
}


int main()
{
   Solution solution;

   string s("catsanddog");
   vector<string> wordDict = { "cat", "cats", "and", "sand", "dog" };


   auto result = solution.wordBreak(s, wordDict);
   print(result);
   return 0;
}
