/*
Letter Combinations of a Phone Number

You are given a string digits made up of digits from 2 through 9 inclusive.

Each digit (not including 1) is mapped to a set of characters as shown below:

A digit could represent any one of the characters it maps to.

Return all possible letter combinations that digits could represent. You may return the answer in any order.



Example 1:

Input: digits = "34"

Output: ["dg","dh","di","eg","eh","ei","fg","fh","fi"]
Example 2:

Input: digits = ""

Output: []
Constraints:

0 <= digits.length <= 4
2 <= digits[i] <= 9

*/

class Solution {
private:
    inline static const vector<vector<char>> KEY_BOARD = {
        {}, // 0
        {}, // 1

        {'a','b','c'},    // 2
        {'d','e','f'},    // 3
        {'g','h','i'},    // 4
        {'j','k','l'},    // 5
        {'m','n','o'},    // 6
        {'p','q','r','s'},// 7
        {'t','u','v'},    // 8
        {'w','x','y','z'} // 9
    };

    void combination(int from, const string& digits, 
                    string current,
                    vector<string>& res){
        if(from == digits.size()) { res.push_back(current); return;}

        const auto& digit = digits[from] - '0';
        for(auto letter : KEY_BOARD[digit]){
            combination(from+1, digits, current + letter, res);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<string> res;
        combination(0, digits, "", res);
        return res;
    }
};

