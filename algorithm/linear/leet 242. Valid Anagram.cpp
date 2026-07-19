class Solution {
public:
    bool isAnagram(string s, string t) 
    {
        if(s.size() != t.size())
            return false;
    
        unordered_map<char, int> toMatch;
        for(char c:t )
        {
            ++toMatch[c];
        }
        
        for(char c:s)
        {
            --toMatch[c];
        }
        
        for(auto it : toMatch)
        {
            if(it.second!=0)
                return false;
        }
        //O(N+M)
        return true;
    }
    

    
    bool isAnagram_sort(string s, string t) {
        sort(s.begin(), s.end());        
        sort(t.begin(), t.end());
        //O(NlogN + MlogM)
        return s==t;
    }
};
