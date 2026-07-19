class Solution 
{
public:
    /**
     * @param s: the string
     * @return: Min Deletions To Obtain String in Right Format
     */
    int minDeletionsToObtainStringInRightFormat(string &s) 
    {
        // write your code here

        size_t leftBCount = 0;
        size_t rightACount = 0;

        for(char c : s)
        {
            if(c == 'A') ++rightACount;
        }
        
        size_t minDeletions = std::min(rightACount, s.size() - rightACount);//All A or all B

        for(size_t i = 0; i<s.size()-1; ++i)
        {
            if(s[i] == 'A') 
            {
                --rightACount;
            }
            else
            {
                ++leftBCount;
            }
            if(s[i] == 'A' && s[i+1]=='B')
                minDeletions = std::min(minDeletions, leftBCount+rightACount);

        }
    
        return minDeletions;
    }


};
