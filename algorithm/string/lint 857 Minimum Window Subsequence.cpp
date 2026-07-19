class Solution {
/*

Given two strings s and t, return the shortest substring of s such that every character in t, including duplicates, is present in the substring. If such a substring does not exist, return an empty string "".

You may assume that the correct output is always unique.

Example 1:

Input: s = "OUZODYXAZV", t = "XYZ"

Output: "YXAZ"
Explanation: "YXAZ" is the shortest substring that includes "X", "Y", and "Z" from string t.

Example 2:

Input: s = "xyz", t = "xyz"

Output: "xyz"
Example 3:

Input: s = "x", t = "xy"

Output: ""
Constraints:

1 <= s.length <= 1000
1 <= t.length <= 1000
s and t consist of uppercase and lowercase English letters.
*/
public:
    string minWindow(string s, string t) {
        // need all letters in t, we need a match histogram:
        unordered_map<char, int> toBematched;
        for(const char c:t) 
            ++toBematched[c];

        unordered_map<char, int> current;
        auto match = [](const unordered_map<char, int> & toBematched, 
                        const unordered_map<char, int> &current){
            for(const auto & [c, count]:toBematched){
                if(!current.contains(c)) 
                    return false;
                if(current.find(c)->second < count) 
                    return false;

                return true;
            }
        };

        //sliding window check if the map was mached. 
        int left = 0;
        int right = 0;

        int res = -1;
        int resLen = INT_MAX;

        int matches = 0;

        while(right<s.size()){
            if(toBematched.contains(s[right])){
                ++current[s[right]];
                if(current[s[right]] == toBematched[s[right]]){
                    ++matches;
                }

                while(matches == toBematched.size()){ // try to reduce the length by moving left 
                    //matches, let's note it 
                    if(right-left+1 < resLen){
                        res = left;
                        resLen = right-left+1;
                    }
                    
                    if(toBematched.contains(s[left])){
                        --current[s[left]];
                        if(current[s[left]] < toBematched[s[left]]){
                            --matches;// this could break the while condition, then we go to move right.
                        }
                    }
                    ++left;// left should move anyway, even it breakes the matches, we have to go, in order to move to next substr who matches.
                }
            }
            ++right;
        }

        return res == -1 ? "" : s.substr(res, resLen);
    }
};
