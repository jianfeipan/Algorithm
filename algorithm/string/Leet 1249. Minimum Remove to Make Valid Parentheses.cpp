class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<size_t> opens;
        
        for(size_t i = 0; i<s.size(); ++i)
        {
            if(s[i] == '(') opens.push(i);
            else if(s[i] == ')')
            {
                if(opens.empty()) s[i] = '*';
                else opens.pop();
            }
        }
        
        while(!opens.empty()) s[opens.top()] = '*',opens.pop();
        
        string validStr("");
        
        for(auto c : s) if(c != '*') validStr+=c;
        
        return validStr;
    }
};
