class Solution {
public:
    int mySqrt(int x) 
    {
        if(x<=1) return x;
        
        int left = 1;
        int right = x;
        
        while(left<right)
        {
            const int mid = ((right-left)>>1) + left;// (right+left)>>1 --->to avoid int overflow
            
            if(mid<=x/mid)//mid*mid<=x --> to avoid int overflow, we use divide
            {
                if (mid + 1 > x/(mid + 1))
                    return mid;
                left = mid+1;
            }
            else
            {
                right = mid-1;
            }
        }
        
        return left;
        
    }
};  
