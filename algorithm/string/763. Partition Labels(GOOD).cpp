
/*
You are given a string s consisting of lowercase english letters.

We want to split the string into as many substrings as possible, while ensuring that each letter appears in at most one substring.

Return a list of integers representing the size of these substrings in the order they appear in the string.

Example 1:

Input: s = "xyxxyzbzbbisl"

Output: [5, 5, 1, 1, 1]
Explanation: The string can be split into ["xyxxy", "zbzbb", "i", "s", "l"].

Example 2:

Input: s = "abcabc"

Output: [6]


*/



/*
idea:
    each letter appears in at most one substring
"xyxxyzbzbbisl"
[5, 5, 1, 1, 1]

when I take x, I need to cover all the index of x [min, max]
then I take letter max+1

I need a structure to have the indexes in order for each letter:

unordered_map<char, vector<int>> (we push index from left to right, it's naturally in order)
array<vector<int>, 26>
*/
class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> letterLastIndex;
        for(int i=0; i<s.size(); ++i){
            letterLastIndex[s[i]] = i;
        }

        vector<int> subStrLen;
        int l = 0;
        while(l<s.size()){
            int r = letterLastIndex[s[l]];
            for(int i=l; i<=r; ++i){
                // extend r to include all letter in current r
                r = max(r, letterLastIndex[s[i]]);
            }
            subStrLen.push_back(r-l+1);
            l=r+1;
        }
        
        return subStrLen;

    }
};
