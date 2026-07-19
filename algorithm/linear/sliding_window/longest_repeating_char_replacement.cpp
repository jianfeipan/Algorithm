/*
Longest Repeating Character Replacement

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
        // chaneg k chars : means i can have a most presented char in my window, then other k what ever letters.

        int l=0, r=0;
        array<int, 26> window{};

        int most_freq = 0;
        int max_len = 0;
        while( r<s.size() ) {
            ++window[s[r] - 'A'];
            most_freq = max(most_freq, window[s[r] - 'A']);

            if(r - l + 1 - most_freq > k){
                // move left to deshrink the the window: we are sur with one move the k conditionis good
                --window[s[l] - 'A'];// no worries the max, it will be reset in next circle
                ++l;
            }
            
            max_len = max(max_len, r - l +1);
            ++r;
        }

        return max_len;
    }
};

