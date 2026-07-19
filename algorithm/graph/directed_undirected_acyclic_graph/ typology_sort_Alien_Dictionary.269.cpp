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
class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, unordered_set<char>> prefix;
        unordered_map<char, unordered_set<char>> postfix;

        unordered_set<char> letters;
        for (const auto& word : words) {
            for (char c : word) {
                letters.insert(c);
            }
        }   

        for(int i=1; i<words.size(); ++i){
            const auto& left = words[i-1];
            const auto& right = words[i];

            int min_len = min(left.size(), right.size());
            int c = 0;

            for(; c < min_len; ++c){
                if(left[c] != right[c]){
                    prefix[right[c]].insert(left[c]);
                    postfix[left[c]].insert(right[c]);
                    break;
                }
            }

            // invalid case
            if(c == min_len && left.size() > right.size()) return "";
        }

        // typology sort
        queue<char> visit;
        for(auto letter : letters){
            if(prefix[letter].empty()) visit.push(letter);
        }
        string sorted;
        while(!visit.empty()){
            auto cur = visit.front();visit.pop();
            sorted.push_back(cur);
            for(auto next : postfix[cur]){
                prefix[next].erase(cur);
                if(prefix[next].empty()) visit.push(next);
            }
        }

        return sorted.size() == letters.size() ? sorted : "";

    }
};

