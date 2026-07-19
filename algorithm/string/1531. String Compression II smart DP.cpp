class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) 
    {
        cache = vector<vector<int>>(s.size(), vector<int>(k+1, -1));
        
        return getLengthOfOptimalCompression_smarDP(s, 0, k );
    }

    
    int getLengthOfOptimalCompression_smarDP(const string & s, int left, int k) 
    {   
        
        if(k < 0) return 100;  // invalid, return INF
        if(left >= s.size() || s.size() - left <= k) return 0;  // empty
        
        int minLen = cache[left][k];
        if( minLen!=-1) return minLen;
        
        
        int count[26] = {0};
        // we try to make s[left:j] (both inculded) as one group,
        // and all chars in this group should be the same.
        // so we must keep the most chars in this range and remove others
        // the range length is (j - left + 1)
        // and the number of chars we need to remove is (j - left + 1 - most)
        minLen = s.size();
        
        int charMaxCount = 0;
        for(int j = left; j < s.size(); ++j) {
            charMaxCount = max(charMaxCount, ++count[s[j] - 'a']);  // charMaxCount = max(count(s[left:j])
            
            minLen = min(minLen, 
                         1//the char 
                         + numLen(charMaxCount) //char's count
                         + getLengthOfOptimalCompression_smarDP(s, j + 1, k - (j - left + 1 - charMaxCount)));
        }
        
        cache[left][k] = minLen;
        return minLen;
    }
    
private:
    int numLen(int num)
    { return num == 1 ? 0 : num < 10 ? 1 : num < 100 ? 2 : 3; }
   
private:
    vector<vector<int>> cache;
    
};
