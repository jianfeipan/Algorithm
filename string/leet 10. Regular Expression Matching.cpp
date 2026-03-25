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
    bool dfs(const string& s, const string& p, int i, int j){
        if(p.size() == j) return s.size() == i;
        if(s.size() == i){ // s is over
            if(j+1<p.size() && p[j+1] == '*') // following a *
                return dfs(s, p, i, j+2); // only .* a* b* left
        }

        if(s[i] == p[j] || p[j] == '.'){ // match
            if(j+1<p.size() && p[j+1] == '*'){ // following a *
                return dfs(s, p, i+1, j)  // skip the current letter try i+1
                    || dfs(s, p, i, j+2); // skip the .* patern try j+2
            }
            return dfs(s, p, i+1, j+1); // no *, single letter match
        }else{ // miss
            if(j<p.size()-1 && p[j+1] == '*'){ //  following a *
                return dfs(s, p, i, j+2); // skip the .*
            }
            
            return false; // no * single letter miss match
        }



    }
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0, 0);
    }
};
