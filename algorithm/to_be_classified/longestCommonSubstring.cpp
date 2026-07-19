 string longestCommonSubstring(const string & left, const string & right)
    {
        
        int maxLen = 0;
        int maxEnd = left.size() -1;
        int compareGrap[left.size()][right.size()];
        for(int i=0; i<left.size(); ++i)
        {
            for(int j=0; j<right.size(); ++j)
            {
                if(left[i] == right[j])
                {
                    if(i==0 || j==0)
                    {
                        compareGrap[i][j] = 1;
                    }else
                    {
                        compareGrap[i][j] = compareGrap[i-1][j-1] + 1;
                    }
                    
                    if(maxLen<compareGrap[i][j])
                    {
                        maxLen = compareGrap[i][j];
                        maxEnd = i;
                    }
                    
                }
                else
                {
                    compareGrap[i][j] = 0;
                }
            }
        }
        
        return left.substr(maxEnd+1-maxLen, maxLen); 
    }
