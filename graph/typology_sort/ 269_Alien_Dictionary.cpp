/*
Alien Dictionary
Solved 
Hard
Topics
Company Tags
Hints
There is a foreign language which uses the latin alphabet, but the order among letters is not "a", "b", "c" ... "z" as in English.

You receive a list of non-empty strings words from the dictionary, where the words are sorted lexicographically based on the rules of this new language.

Derive the order of letters in this language. If the order is invalid, return an empty string. If there are multiple valid order of letters, return any of them.

A string a is lexicographically smaller than a string b if either of the following is true:

The first letter where they differ is smaller in a than in b.
a is a prefix of b and a.length < b.length.
Example 1:

Input: ["z","o"]

Output: "zo"
Explanation:
From "z" and "o", we know 'z' < 'o', so return "zo".

Example 2:

Input: ["hrn","hrf","er","enn","rfnn"]

Output: "hernf"
Explanation:

from "hrn" and "hrf", we know 'n' < 'f'
from "hrf" and "er", we know 'h' < 'e'
from "er" and "enn", we know get 'r' < 'n'
from "enn" and "rfnn" we know 'e'<'r'
so one possibile solution is "hernf"
Constraints:

The input words will contain characters only from lowercase 'a' to 'z'.
1 <= words.length <= 100
1 <= words[i].length <= 100


idea:

two pointer comparison, letter[i] and letter[i+1]: 
  - we got a successor graph
  - we also need a counter map to know: how many letters are prerequisits
["hrn","hrf","er","enn","rfnn"]
n->f
h->e
r->n
e->r

f 1
e 1
n 1
r 1
h = 0!!!!-> need initialization
*/

#include <array>
class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, unordered_set<char>> suffix;
        unordered_map<char, int> prefixCout;
        for(auto& word:words) for(auto& c:word) prefixCout[c] = 0;

        for(int i=1; i<words.size(); ++i){
            auto& left = words[i-1];
            auto& right = words[i];

            int len = min(left.size(), right.size());
            int j=0;
            for(; j<len; ++j){
                const auto& l = left[j];
                const auto& r = right[j];
                if(l != r){ 
                    if(!suffix[l].count(r)){
                        suffix[l].insert(r);
                        ++prefixCout[r];
                    }
                    break;
                }
            }
            if(j==len){
                if(left.size() > right.size()) return ""; // invalid order
            }
        }

        //typology sort
        string order;
        queue<char> noPrefix;
        for(const auto&[c, pres]:prefixCout){
            if(pres==0) noPrefix.push(c);
        } 

        while(!noPrefix.empty()){
            auto current = noPrefix.front(); noPrefix.pop();
            for(const auto& c : suffix[current]){
                --prefixCout[c];
                if(prefixCout[c]==0) noPrefix.push(c);
            }
            order+=current;
        }

        return order.size()<prefixCout.size() ? "" : order;
    }
};

