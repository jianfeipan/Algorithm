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
    vector<vector<int>> memory;
    int match_from(int i, int j, const string& s, const string& t){
        if(j == t.size()) return 1;
        if(i == s.size()) return 0;

        auto& cache = memory[i][j];
        if(cache != -1) return cache;

        int match = match_from(i+1, j, s, t);
        if(s[i] == t[j]) match += match_from(i+1, j+1, s, t);

        return cache = match;

    }
public:
    int numDistinct(string s, string t) {
        memory = vector<vector<int>>(s.size(), vector<int>(t.size(), -1));
        return match_from(0, 0, s, t);
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

