class Solution {
public:
    string decodeString(string s) {
        //Regex
        //Recusive
        int start = 0;
        return decode(s, start);
    }
    
public:
    string decode(const string & s, int & i)//this is passed as reference is very trick : we want to continue on the string in recusive calls
    {
        string decoded;
        
        while(i<s.size() && s[i]!=']')
        /* 
        here the  s[i]!='] is really tricky : it's for avoid ead loop in case : 3[2[a]] : the 2[a] finished and will not do a return, because we may have 2[a]3[b]
        so in "read number" section,  we need to keep going to while without returning the decoded, and so we need this condition to stop with while. 
        */
        {
            //read number
            if(std::isdigit(s[i]))
            {
                int count = readNum(s, i);
                 
                i++;//skip [
                //read next segment
                const string & toBeRepeasted = decode(s,i);
                //output
                for(int repeat= 0; repeat<count; ++repeat)
                {
                    decoded += toBeRepeasted;
                }
                
                ++i;//skip ]
            }
            //read string       
            else if(std::isalpha(s[i]))       
            {
                decoded+=readChars(s,i);
                //we cannot do a return directly here because we may have 2[a3[b]], in this case, after read a, we should go to the while instead of return to uper level.
            }
        }
        return decoded;
               
    }
    
    
private:
    int readNum(const string &s, int & i)
    {
        int count = 0;
        while(i<s.size() && std::isdigit(s[i])) count*=10,count+=(s[i] - '0'),++i;
        
        return count;
    }    
    
    string readChars(const string & s, int & i)
    {
        string chars;
        while(i<s.size() && std::isalpha(s[i])) chars+=s[i],++i;

        return chars;
    }
};
