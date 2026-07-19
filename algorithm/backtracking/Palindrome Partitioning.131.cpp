/*
Given a string s, split s into substrings where every substring is a palindrome. Return all possible lists of palindromic substrings.

You may return the solution in any order.

Example 1:

Input: s = "aab"

Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"

Output: [["a"]]
Constraints:

1 <= s.length <= 20
s contains only lowercase English letters.-
*/
class Solution {
private:
    bool is_palindrome(const string& s){
        int l = 0;
        int r = s.size() - 1;
        while(l < r){
            if(s[l]!=s[r]) return false;
            ++l;
            --r;
        }
        return true;
    } 

    void partition( string s, 
                    vector<string>& current,
                    vector<vector<string>>& res){
        if(s.empty()) { res.push_back(current); return; }

        for(int i=0; i<s.size(); ++i){
            auto str = s.substr(0, i+1);
            if(is_palindrome(str)){
                current.push_back(str);
                partition(s.substr(i+1), current, res);
                current.pop_back();
            }
        }

    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> current;
        partition(s, current, res);
        return res;
    }
};

