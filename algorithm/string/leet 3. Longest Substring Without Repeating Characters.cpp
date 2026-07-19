class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;
        if(s.size() == 1) return 1;

        int maxLen = 1;
        unordered_set<char> chars;
        chars.insert(s[0]);
        int i = 0;
        int j = 1; 
        while(j<s.size()){
            const char current = s[j];
            //duplication
            if(chars.count(current) == 0){
                chars.insert(current);
            } else{
                maxLen = max(maxLen, j-i);
                while(s[i] != current){
                    chars.erase(s[i]);
                    ++i;
                }//move to the duplicated position
                ++i;// goover the duplication
            }
            ++j;
        }
        if(j==s.size())
            maxLen = max(maxLen, j-i);

        // 0 1 2 3 4 5 6 7
        // a b c a b c d d
        // i.    j
        // i need to go right remove the letters from set, util no more duplications
        return maxLen;
    }



// similar idea: but easyer to understand
    int lengthOfLongestSubstring(string s) 
    {
        int maxLen = 0;
        
        //unordered_set<char> current;
        int current[256] = {0};//use bitmap
        int left=0;
        int right = 0;
        
        while(right< s.size())
        {
            while(current[s[right]] )//right letter is in current map--> i need to move left to remove this duplication
            {
                current[s[left]]=0;
                ++left;
            }
            
            current[s[right]] = 1;// no more duplication on right, mark right in current, move to next
            right++;
            if(right - left +1 > maxLen)//every time right increase one, we have the possiblility to have a max length 
            {
                maxLen = right - left;
            }
           
        }
        
        return maxLen;
        
    }
};
