class Solution {
public:
    int hammingDistance(int x, int y) {
        int distance = 0;
        int xored = x^y;
        
        bitset<16> xb(x);
        bitset<16> yb(y);
        bitset<16> zb(xored);
        cout<<xb<<endl<<yb<<endl<<zb<<endl;
        
        
        while(xored)
        {
            distance+= (xored&1);
            xored>>=1;
        }
        
        return distance;
    }
};
