class Solution {

/*

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Example 3:

Input: haystack = "", needle = ""
Output: 0

*/
public:
    int strStr(string haystack, string needle) {
        return strStr_KMP(haystack, needle);
    }

    
    int strStr_bructe_force(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();

        for(int i = 0; i<=m - n; ++i)
        {
            int j = 0;
            while(j<needle.size() && needle[j] == haystack[i+j]) ++j;
            
            if(j == needle.size()) return i;
        }
        return -1;
    }
    
    int strStr_KMP(string haystack, string needle) 
    {
        int m = haystack.size(), n = needle.size();
        if (!n) {
            return 0;
        }
        vector<int> lps = kmpProcess(needle);
        
        for(int j = 0,i = 0; i<=m - n;)
        {
            while(j<needle.size() && needle[j] == haystack[i+j]) ++j;
            
            if(j == needle.size()) return i;
            
            if (i < m && haystack[i+j] != needle[j])
            {
                if(j==0) ++i;
                else
                {
                    i += (j -lps[j - 1]);
                    j = lps[j - 1];
                }
            }
        }
        return -1;
    }
    
    
    int strStr_KMP_one_loop(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (!n) {
            return 0;
        }
        vector<int> lps = kmpProcess(needle);
        for (int i = 0, j = 0; i < m;) {
            if (haystack[i] == needle[j]) { 
                i++, j++;
            }
            if (j == n) {
                return i - j;
            }
            if (i < m && haystack[i] != needle[j]) j ? j = lps[j - 1] : i++;
        }
        return -1;
    }
private:
    vector<int> kmpProcess(const string & needle) {
        int n = needle.size();
        vector<int> lps(n, 0);
        /*
            lps will show if we stop on this letter, how many offset do we do to next compare.
            main idea is the number of common  prefix and suffix.
        */
        for (int i = 1, len = 0; i < n;) {
            if (needle[i] == needle[len]) //same letter will make len longer, means you need to come back more 
            {
                ++len;
                lps[i] = len;
                ++i;
            }
            else 
            {
                if (len) len = lps[len - 1];
                else lps[i++] = 0;
            }
        }
        
        //for(int i : lps) cout<<i<<",";
        
        return lps;
    }
};
