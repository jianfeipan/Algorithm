/*Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

 

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false

*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.size() > s2.size()) return false;

        const auto& m = s1.size();
        const auto& n = s2.size(); 

        unordered_map<char, int> target;
        for(auto c : s1) ++target[c];

        unordered_map<char, int> window;
        /*
        s1 = "abc", 3 
        s2 = "lecabee" 7
        0123456
            r        
        lecabee
        */
        int match=0;
        int r=0;
        //build window
        for(; r<m; ++r){
            auto current = s2[r];
            if(target.count(current)){
                ++window[current];
                if(window[current] == target[current]) ++match;   
                else if(window[current] == target[current]+1) --match;
            }
        }
        if(match == target.size()) return true;
        
        // slide fixed window
        int l=0;
        for(; r<n; ++r,++l){
            auto left = s2[l];
            if(target.count(left)){
                --window[left];
                if(window[left] == target[left]) ++match;
                else if(window[left] == target[left]-1) --match;
            }

            auto right = s2[r];
            if(target.count(right)){
                ++window[right];
                if(window[right] == target[right]) ++match;
                else if(window[right] == target[right]+1)--match;
            }
            if(match == target.size()) return true;
        }
        
        
        return false;
    }
};

