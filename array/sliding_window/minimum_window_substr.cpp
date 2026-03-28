class Solution {
public:
    string minWindow(string s, string t) {
        // every char in t is present in the substr of s
        if (t.empty()) return "";

        unordered_map<char, int> countT, window;
        for (char c : t) {
            countT[c]++;
        }

        int have = 0;

        int l=0; 
        int r=0;
        int minLen = INT_MAX;
        int minL = -1;
        while(r<s.size()){
            char c = s[r];
            window[c]++;
            if (countT.contains(c) && window[c] == countT[c]) ++have;

            while(have == countT.size()){// 
                auto len = r-l+1;
                if(len < minLen){
                    minLen = len;
                    minL = l;
                }
                
                --window[s[l]];
                if (countT.contains(s[l]) && window[s[l]] < countT[s[l]]) --have;
                
                ++l;
            }

            ++r;
        }
        
        return minL == -1 ? "" : s.substr(minL, minLen);
        
    }
};
