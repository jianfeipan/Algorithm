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
        unordered_map<char, int> count;
        int maxLen = 0;
        int mostFrequent = 0;
        int l=0;
        int r=0;
        while(r<s.size()){
            ++count[s[r]];
            mostFrequent = max(mostFrequent, count[s[r]]);
            // missing letters is bigger, mostFrequent is the longest we find so far
            // so keep it to be the global max,and we don't need to re do the max for current window.
            while((r-l+1) - mostFrequent >  k){
                --count[s[l]];
                ++l;
            }
            maxLen = max(maxLen, r-l+1);
            ++r;
        }
        
        return maxLen;
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // sub str: order, continue

        unordered_map<char, int> window;

        int l=0;
        int r=0;
        int max_len = 0;
        while(r<s.size()){
            const auto current = s[r];
            if(window.count(current)){
                l = max(l, window[current] + 1); // skip the duplication, and avoid the staled data: max(l, ), so we don't need to remove the elements out of windown when move l
            }
            window[current] = r;// update the new index if need to be remove
            
            max_len = max(max_len, r-l+1);
            ++r;
        }
        return max_len;
    }
};

