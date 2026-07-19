
static bool isNumber(char c)
{
    return c>='0'&& c<='9';
}


int Solution::atoi(const string A) {
    if(A.empty())
        return 0;

    int result=0;
    bool positive = true;

    char first = A[0];
    if(first=='-')
        positive = false;
    else if(first=='+')
        positive = true;
    else if(isNumber(first))
        result+=first-'0';
    else
        return 0;


    for(int i = 1; i<A.size();++i)
    {
        char c = A[i];
        
        if(isNumber(c))
        {
            int toAdd = (c-'0');
            if(positive)
            {
                if(result>INT_MAX/10)
                    return INT_MAX;
                result*=10;
                
                if(result>INT_MAX - toAdd)
                    return INT_MAX;
                result+=toAdd;
            }
            else{
                if(result<INT_MIN/10)
                    return INT_MIN;
                result*=10;
                
                if( result<INT_MIN + toAdd)
                    return INT_MIN;
                result-=toAdd;
            }
        }
        else{
            break;
        }
    }
    return result;
}
