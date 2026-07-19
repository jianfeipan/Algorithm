class Solution {
    /*
    facts:
        subrstring -> order metters
        each substring palindrome.
    idae:
        recursive: 
            if I take the current letter in my current palindrome,
            if I take the current letter as a new substring
    */
private:
    bool is_palindrome(string_view s) {
        int l = 0, r = s.size() - 1;

        while(l<r) {
            if (s[l] != s[r]) return false;
            ++l;
            --r;
        }
        return true;
    }
    void partition_(string_view s, 
                    int index,
                    vector<string>& current,
                    vector<vector<string>>& res) {
        if (index == s.size()) {
            res.push_back(current);
            return;
        }

        // start from index, find a palindrome and call next
        for (int i = index; i<s.size(); ++i) {
            const auto& substr = s.substr(index, i-index+1);
            if (is_palindrome(substr)) {
                current.emplace_back(substr);
                partition_(s, i+1, current, res);
                current.pop_back();
            }
        }
        
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> current;
        partition_(s, 0, current, res);
        return res;
    }
};
