/*
115. Distinct Subsequences

Given two strings s and t, return the number of distinct subsequences of s which equals t.

The test cases are generated so that the answer fits on a 32-bit signed integer.

 

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Example 2:

Input: s = "babgbag", t = "bag"
Output: 5


*/

class Solution {
private:
    int dfs(const string& s,
            const string& t,
            int i, int j, 
            vector<vector<int>>& memory){

        if(j==t.size()) return 1;
        if(i==s.size()) return 0; // s used up, but t still left letters

        auto& cache = memory[i][j];
        if(cache!=-1) return cache;

        int solutions=0;
        if(s[i] == t[j]){
            solutions += dfs(s,t, i+1, j+1, memory);
        }
        solutions += dfs(s,t, i+1, j, memory);
        return cache = solutions;
    }
public:
    int numDistinct(string s, string t) {
        if(t.empty()) return 1;
        if(s.empty()) return 0;

        vector<vector<int>> memory(s.size(), vector<int>(t.size(), -1));

        return dfs(s, t, 0, 0, memory);
        // without memory: O(2^n) evert letter can be take or not
        // with memory: O(m*n) space O(m*n)
    }
};


int main() {
    Solution sol;

    expect(sol.numDistinct("caaat", "cat"), 3, "caaat/cat");
    expect(sol.numDistinct("xxyxy", "xy"), 5, "xxyxy/xy");
    expect(sol.numDistinct("abc", ""), 1, "abc/empty t");
    expect(sol.numDistinct("", "a"), 0, "empty s/a");
    expect(sol.numDistinct("", ""), 1, "empty/empty");
    expect(sol.numDistinct("abc", "abc"), 1, "abc/abc");
    expect(sol.numDistinct("abc", "d"), 0, "abc/d no match");
    expect(sol.numDistinct("aaa", "a"), 3, "aaa/a");
    expect(sol.numDistinct("rabbbit", "rabbit"), 3, "rabbbit/rabbit");
    expect(sol.numDistinct("babgbag", "bag"), 5, "babgbag/bag");
    return 0;
}

