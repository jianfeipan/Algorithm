class Solution {
public:
    string removeDuplicates(string s) {
        deque<char> left;
        for(char c : s)
        {
            if(!left.empty() && c == left.back()) left.pop_back();
            else left.push_back(c);
        }
        
        return string(left.begin(), left.end());
    }
};
