/*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 3 * 104
s[i] is '(', or ')'.
*/


/*
idea:
    from one open to one close, inside is also valide
    BF: look at all substrings and test if they are valid O(N^3)
    recursive: 
        when I find a open, try to find a close and recursively test if between them are valid
        in the same time note the max len
        with memory O(n)

*/
class Solution_DP {
private:
    int longestFrom(const string& s, int from, vector<int>& memory){
        if(from >= s.size()) return 0;

        auto& cache = memory[from];
        if(cache!=-1) return cache;

        if(s[from] == ')') return cache = 0;
        // from: (
        int longest=0;
        int len = longestFrom(s, from+1, memory);
        int to = from+len+1;
        while(to<s.size() && from<s.size() && s[from] == '(' && s[to] == ')'){
            longest+= (len+2);

            from=to+1;
            len = longestFrom(s, from+1, memory);
            to = from+len+1;
        }

        return cache = longest;
    }
public:
    int longestValidParentheses(string s) {
        if(s.size()<=1) return 0;

        vector<int> memory(s.size(), -1);
        int maxLen = 0;
        for(int i=0; i<s.size(); ++i) maxLen = max(maxLen, longestFrom(s, i, memory));
        return maxLen;
    }
};

/*
using stack is another solution O(n)
stack push the index of '(' and pop it when it's ')', every succesful pop, the distance between that open and current close push the max value bigger
*/
class Solution {
public:

    int longestValidParentheses(string s){
        stack<int> opens;
        opens.push(-1); //  we need the bottom one have the position before the first valid open
        int longest = 0;
        for(int i=0; i<s.size(); ++i){
            if(s[i] == '(') opens.push(i);
            else{
                opens.pop();
                if(opens.empty()) opens.push(i); // updating the position before the open
                else{
                    //opens.top() is the position before the last validate opens, which was poped.
                    longest = max(longest, i - opens.top());
                    
                }
            }
        }

        return longest;
    }
};
