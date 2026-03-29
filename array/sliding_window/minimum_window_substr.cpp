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
        if(s.size() < t.size()) return "";

        unordered_map<char, int> target;
        for(auto c : t) ++target[c];

        int minLen=INT_MAX;
        int minLenStart=-1;
        int match = 0;

        int l=0, r=0;
        unordered_map<char, int> current;
        while(r<s.size()){
            const auto& c = s[r];
           
            if(target.contains(c)){
                ++current[c];
                if(target[c] == current[c]){
                    ++match;
                }
                // if it's exact match: 
                // else if(target[c]+1 == current[c]){
                //     --match;
                // }
            }
            
            // match: shrink the left (++l)
            while(match == target.size()){
                const auto len = r-l+1;
                if(len < minLen){
                    minLen = len;
                    minLenStart = l;
                }
                
                if(current.contains(s[l])){
                    --current[s[l]];
                    if(current[s[l]] == target[s[l]]-1) --match;
                    // exact match : if(current[s[l]] == target[s[l]]-1) --match;
                }
                ++l;
            }

            ++r;
        }

        return minLenStart==-1? "" : s.substr(minLenStart, minLen);
    }
};
