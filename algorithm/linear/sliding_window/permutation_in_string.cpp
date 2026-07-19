/*
Permutation in String
Return true if s2 contains a permutation of s1, or false otherwise. That means if a permutation of s1 exists as a substring of s2, then return true.

Both strings only contain lowercase letters.

Example 1:

Input: s1 = "abc", s2 = "lecabee"

Output: true
Explanation: The substring "cab" is a permutation of "abc" and is present in "lecabee".

Example 2:

Input: s1 = "abc", s2 = "lecaabee"

Output: false
*/

/*
substring: means the window's size is fixed!!!

*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        /*
        s1 : abc
        s2:  lec| aabee

        initialize the histogram with s1.size()          
        */

        vector<int> s1Count(26, 0);
        vector<int> s2Count(26, 0);
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }
        /*
            count matches        
        */
        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1Count[i] == s2Count[i]) {
                matches++;
            }
        }

        /* slide the fixed window of s1.size() */
        int l = 0;
        int r = s1.length();
        while(r < s2.length()){
            if (matches == 26) return true;// all match

            auto i = s2[r] - 'a';
            s2Count[i]++;
            if (s1Count[i] == s2Count[i]) {
                matches++;
            } else if (s1Count[i] + 1 == s2Count[i]) {
                matches--;
            }

            i = s2[l] - 'a';
            s2Count[i]--;
            if (s1Count[i] == s2Count[i]) {
                matches++;
            } else if (s1Count[i] - 1 == s2Count[i]) {
                matches--;
            }
            l++;
            r++;
        }
        return matches == 26;
    }
};
