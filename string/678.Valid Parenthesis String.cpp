/*
Valid Parenthesis String


You are given a string s which contains only three types of characters: '(', ')' and '*'.

Return true if s is valid, otherwise return false.

A string is valid if it follows all of the following rules:

Every left parenthesis '(' must have a corresponding right parenthesis ')'.
Every right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
A '*' could be treated as a right parenthesis ')' character or a left parenthesis '(' character, or as an empty string "".
Example 1:

Input: s = "((**)"

Output: true
Explanation: One of the '*' could be a ')' and the other could be an empty string.

Example 2:

Input: s = "(((*)"

Output: false
Explanation: The string is not valid because there is an extra '(' at the beginning, regardless of the extra '*'.


*/


/*
idea:
    if there is no *:   
        stack: pus opens, pop when it's a close
        since we only have () and *, we can do with a counter
        if ( ++i
        if ) --i: negative i means novalid, in the end i!=0: novalid
    with *: 
        - we can do i++ or i-- or nothing
        - three branches
            -> recursive valid(from, i, s)
                if any branch is true, then true, or false;

*/
class Solution {
private:
    bool valid(const string& s, int from, int opens, vector<vector<int>>& memory){
        if(from == s.size()) return opens==0;
        if(opens<0) return false;

        auto& cache = memory[from][opens];
        if(cache!=-1) return cache;

        if(s[from] == '(') return cache = valid(s, from+1, opens+1, memory);
        if(s[from] == ')') return cache = valid(s, from+1, opens-1, memory);
        //if(s[from] == '*')
        return cache = (
               valid(s, from+1, opens, memory) 
            || valid(s, from+1, opens+1, memory)
            || valid(s, from+1, opens-1, memory));
    }
public:
    bool checkValidString(string s) {
        vector<vector<int>> memory(s.size(), vector<int>(s.size(), -1));
        return valid(s, 0, 0, memory);
    }
};
