int Solution::reverse(int A) {
    int reversed = 0;
    while(A!=0)
    {
        int current = A%10;
        reversed+=current;
        A/=10;
        if(A!=0)
        {
            if(reversed<INT_MIN/10 || reversed>INT_MAX/10)
                return 0;
            reversed*=10;
        }
    }
    return reversed;
}
