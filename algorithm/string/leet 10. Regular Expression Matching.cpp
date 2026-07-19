/*
'.' Matches any single character
'*' Matches zero or more of the preceding element.

idea:
    two pointers
    using a recursive way: 
        if match 
            following * ? 
             yes->  skip star j+2 or skip letter i+1
             no-> i+1, j+i
         if not match
             following * ?
                 yes -> skip * j+2
                 no -> false ! miss
            



*/

class Solution {
private:
    bool match(int pos_s, int pos_p, const string& s, const string& p){
        if(pos_p == p.size()) return pos_s == s.size();

        auto has_star = (pos_p+1 < p.size() && p[pos_p+1] == '*');

        if(has_star) if(match(pos_s, pos_p+2, s, p)) return true; // current match or not, start matches nothing

        if(pos_s < s.size() && (s[pos_s] == p[pos_p] ||  p[pos_p] == '.')){
            if(has_star){
                if(match(pos_s+1, pos_p, s, p)) return true;// current match doesn't consume the start
                if(match(pos_s+1, pos_p+2, s, p)) return true; // current match consumes the start
            } 
            else{
                if(match(pos_s+1, pos_p+1, s, p)) return true;// no start, match consumes the match or '.'
            }
        }
        
        return false;
    }
public:
    bool isMatch(string s, string p) {
        return match(0, 0, s, p);
    }
};

