#include <sstream>

class ZigzagConversion 
{
public:
    string convert(string s, int numRows) 
    {
        if(numRows<=1)
            return s;
        string res(s);
        int cout = 0;
        const size_t interval = (numRows*2-2);
        for(int line = 0; line<numRows; line++)
        {
            for( int row = line; row<s.size(); row+= interval)
            {
                res[cout++]=s[row]; 

                if(line>0 && line<numRows-1)
                {
                    const int interRowIndex = row+interval-line*2;
                    if(interRowIndex<s.size())
                        res[cout++]=s[interRowIndex];
                }
                
            }
        }
        
        return res;
    }
};
