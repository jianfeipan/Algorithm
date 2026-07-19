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


class Solution {
private:
    void generate(int opens,
                  int n, 
                  string& current,
                  vector<string>& res) {
        if (current.size() == 2*n) {
            res.push_back(current);
            return;
        }

        // put a open
        if(opens<n) { // when i have n open, no more open to put
            current+='(';
            generate(opens+1, n, current, res);
            current.pop_back();// backtracing
        }

        // put a close
        auto closes = current.size() - opens;
        if(opens > closes) { // i can only put close when I have more open to close
            current+=')';
            generate(opens, n, current, res);
            current.pop_back();// backtracing
        } 
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string current;
        generate(0, n, current, res);
        return res;
    }
};
