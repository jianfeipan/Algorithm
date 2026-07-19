class Solution {
public:
    /**
     * @param s: input string
     * @return: a string as the longest palindromic substring
     */




    string longestPalindrome_DP(string &s) {
        int len = s.length();
        vector<vector<int>> isPalindrome(len, vector<int>(len));
        int maxLen = 1;
        int start = 0;
        
        // 将长度为 1 的 dp 值设为真
        for (int i = 0; i < len; i++) {
            isPalindrome[i][i] = 1;
        }
        for (int i = 0; i + 1 < len; i++) {
            if (s[i] == s[i + 1]) {
                isPalindrome[i][i + 1] = 1;
                maxLen = 2;
                start = i;
            }
        }
        for (int left = len - 1; left >= 0; left--) {
        /*
            这里left逆序的原因是 ：isPalindrome[left][right] 的结论需要 油 isPalindrome[left + 1][right - 1] 来推
            可以看出 left 取决于 left +1， 所以left的方向是要从大到小
            而right正好相反 

        */
            for (int right = left + 2; right < len; right++) {

                cout<<left<<","<<right<<endl;
                if (isPalindrome[left + 1][right - 1] == 1
                        and s[left] == s[right]) {
                    
                    isPalindrome[left][right] = 1;
                    // 更新答案
                    if (right - left + 1 > maxLen) {
                        maxLen = right - left + 1;
                        start = left;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }

    //_scann_centers
    string longestPalindrome(string &s) //O(N^2)
    {
        /*
        travaseral all point, take them as center point and try to count from this center to left and right to get the maximum
        
        */ 
        if(s.size()<=1) return s;
        size_t maxLen = 1;
        size_t maxStart = 0;

        auto countFrom = [s](int left, int right, size_t & maxLen, size_t & maxStart){

                while(left>=0 && right<s.size() && s[left] == s[right])
                {
                    --left;
                    ++right;
                }
                ++left;
                --right;
                const int len = right- left + 1;
                if(maxLen < len)
                {

                    maxLen = len;
                    maxStart = left;
                }
        };

        for(size_t center = 1; center<s.size(); ++center)
        {
            //count "aba" patern
            {
                int left = center -1;
                int right = center + 1;

                countFrom(left, right, maxLen, maxStart);
            }



            //count "baab" patern
            {
                int left = center -1;
                int right = center;

                countFrom(left, right, maxLen, maxStart);

            }
        }
        return s.substr(maxStart, maxLen);
    }

    string longestPalindrome_brute_force(string &s)  //O(N^3)
    {
        /*
        idea1 :  cbrute force : traversal all substrings : o(N^2) and check if is palindromic o(N^2 * N) = O(N^3)

        
        
        */ 
        if(s.size()<=1) return s;
        size_t maxLen = 1;
        size_t maxStart = 0;

        size_t left = 0;
        size_t right = 0;
        for(size_t left = 0; left<s.size(); ++left)
        {
            for(size_t right = left+1; right<s.size(); ++right)
            {
                    if(isPalindromic(s, left, right))
                    {
                        if(maxLen<right-left+1)
                        {
                            maxLen = right-left+1;
                            maxStart = left;
                        }
                    }
            }
        }
        return s.substr(maxStart, maxLen);
    }

private:
    bool isPalindromic(const string & s, size_t from, size_t to)
    {
        while(from<to)
        {
            if(s[from]!=s[to])
                return false;
            ++from;
            --to;
        }
        return true;
    }
};
