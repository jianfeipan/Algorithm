/*
window in s has all letters in t including duplications:
    - not a exact match: window can have exact number of letter in c or more!


Input: 
     l    r
s = "OUZODYXAXZV", 
t = "XYZX"
window: 
    match: ++l : when its a match update minLen
    else: ++r 
macth: 
    all chars and duplications-> use a data strucutre to count
    unorderd_map<char, int> 
    uppercase and lowercase? is case sensitive? 

s="ADOBECODEBANC"
t="ABC"

*/
class Solution {
public:
    string minWindow(string s, string t) {
        if(t.size() > s.size()) return "";

        unordered_map<char, int> target;
        for(auto c : t) ++target[c];

        unordered_map<char, int> window;
        int l = 0; 
        int match = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        for(int r=0; r<s.size(); ++r){
            auto right = s[r];
            if(target.count(right)){
                ++window[right];
                if(window.at(right) == target.at(right)){
                    ++match;
                    while(match == target.size()){
                        auto len = r-l+1;
                        if(minLen > len){
                            minLen = len;
                            minStart = l;
                        }
                        // try to shrink the window
                        auto left = s[l];
                        if(target.count(left)){
                            --window[left];
                            if(window.at(left) == target.at(left)-1) --match;
                        }
                        ++l;
                    } 
                }
            }
        }

        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};
