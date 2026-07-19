/*
Decode Ways
A string consisting of uppercase english characters can be encoded to a number using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode a message, digits must be grouped and then mapped back into letters using the reverse of the mapping above. There may be multiple ways to decode a message. For example, "1012" can be mapped into:

"JAB" with the grouping (10 1 2)
"JL" with the grouping (10 12)
The grouping (1 01 2) is invalid because 01 cannot be mapped into a letter since it contains a leading zero.

Given a string s containing only digits, return the number of ways to decode it. You can assume that the answer fits in a 32-bit integer.

Example 1:

Input: s = "12"

Output: 2

Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: s = "01"

Output: 0
Explanation: "01" cannot be decoded because "01" cannot be mapped into a letter.

Constraints:

1 <= s.length <= 100
s consists of digits
*/


/*
ideas:
    1012
    1: 1
    10: 1
    101: 1
    1012: 2

    12123
    1 :1
    12: 2
    121: 2+1=3

    DP:
                                    "1"                  "12"
        numDecodings(from) = numDecodings(from+1) + numDecodings(from+2)

        

*/
class Solution {
private:
    vector<int> memory;
    int dfs(int from, const string& s){
        if(from == s.size()) return 1;

        auto& cache = memory[from];
        if(cache != -1) return cache;

        auto cur = s[from];
        if(cur == '0') return 0;

        auto count = dfs(from + 1, s);// take cur as single

        if(from+1<s.size()){ // possible to take two
            if(cur == '1')  count+=dfs(from+2, s);
            else if(cur = '2' && s[from+1] <= '6') count+= dfs(from + 2, s);
        }

        return cache = count;
        
    }
public:
    int numDecodings(string s) {
        memory = vector<int>(s.size(), -1);
        return dfs(0, s);
    }
};
