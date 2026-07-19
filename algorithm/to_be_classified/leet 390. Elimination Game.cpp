class Solution {
public:
    int lastRemaining(int n) 
    {
        int current=1;
        int step=1;
        bool toRight=true; 
        while (n>1) 
        {
            if (toRight)
                current+=step;
            else
                current += n%2==0? 0 : step;
            
            step*=2;
            n/=2;
            toRight=!toRight;
        }
        return current;
    }
};
