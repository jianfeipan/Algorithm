class Solution {
  
  /*
  Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.

 

Example 1:

Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.
Example 2:

Input: s = "aba"
Output: false
Example 3:

Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
  
  */
public:
    bool repeatedSubstringPattern(string s) 
    {
        for(size_t len = 1; len<=s.size()/2; ++len)
        {
            if(s.size()% len == 0) 

            if(repeatFrom(len, s)) return true;
        }
        return false;       
    }
    
private:
    bool repeatFrom(size_t len, const string & full) 
    {
        for(size_t i = len; i<full.size();)
        {
            for(size_t j = 0; j<len; ++j, ++i)
            {
                if(full[j] != full[i]) return false;
            }
        }
        return true;
    }

               
};
