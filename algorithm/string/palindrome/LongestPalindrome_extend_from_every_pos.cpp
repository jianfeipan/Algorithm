class LongestPalindrome {
class Solution {
public:
    string longestPalindrome(string s) {
        int max_len = 0;
        int max_len_start = -1;

        auto extend = [&](int l, int r, const string& s){
            if(0<=l && r<s.size()){
                while(0<=l && r<s.size() && s[l] == s[r]) { --l; ++r;}
                ++l; --r;// on step back 
                auto len = r-l+1;
                if(max_len < len) { max_len = len; max_len_start = l;}
            }
        };
        
        // from one letter
        for(int i=0; i<s.size(); ++i) extend(i, i,  s);

        // from two letters
        for(int i=0; i<s.size(); ++i) extend(i, i+1,  s);

        return s.substr(max_len_start, max_len);
    }
};
