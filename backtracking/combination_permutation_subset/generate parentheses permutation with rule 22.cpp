/*
You are given an integer n. Return all well-formed parentheses strings that you can generate with n pairs of parentheses.

Example 1:

Input: n = 1

Output: ["()"]
Example 2:

Input: n = 3

Output: ["((()))","(()())","(())()","()(())","()()()"]
You may return the answer in any order.

Constraints:

1 <= n <= 7
*/

class Solution {
private:
    void permute(int open, int close, int n, string current, vector<string>& res){
        if(open == n && close == n) { res.push_back(current); return; }
        //try to put open
        if(open < n) permute(open+1, close, n, current+"(", res);
        // try to put close
        if(close < open) permute(open, close+1, n, current+")", res);

        // no need to trace back, because we are copy current in all recursions
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        permute(0, 0, n, "", res);
        return res;
    }
};