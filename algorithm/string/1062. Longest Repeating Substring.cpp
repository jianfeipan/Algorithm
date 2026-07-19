/*
You are given a string s consisting of only uppercase english characters and an integer k. You can choose up to k characters of the string and replace them with any other uppercase English character.

After performing at most k replacements, return the length of the longest substring which contains only one distinct character.

Example 1:

Input: s = "XYYX", k = 2

Output: 4
Explanation: Either replace the 'X's with 'Y's, or replace the 'Y's with 'X's.

Example 2:

Input: s = "AAABABB", k = 1

Output: 5
Constraints:

1 <= s.length <= 1000
0 <= k <= s.length

*/

class Solution {
public:
    int characterReplacement(string s, int k) {

        if(s.size() <= k+1) return s.size();

        unordered_map<char, int> count;

        int maxLen=1;
        int left = 0;
        ++count[s[left]];
        int mostFrequentLetterNum = 1;
        int right = 1;

        while(right<s.size()){
            const char current = s[right];
            ++count[current];
            mostFrequentLetterNum = max(mostFrequentLetterNum, count[current]);
            // Do i need to replace it?
            // if current is the top frequent letter: i will replace other letters to this one
            while( right - left +1  - mostFrequentLetterNum >k)
            { //and we still cover it
                --count[s[left]];
                ++left;
            }
            maxLen = max(maxLen, right - left +1);
            ++right;
        }
        return maxLen;
    }
};
