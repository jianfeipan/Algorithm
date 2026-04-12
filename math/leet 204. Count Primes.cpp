class Solution {

// n = 5:
//    0 1 2 3 4 5 6 7 8 9 
//    f f t t t t t t t
//2-> t t t t f t f t f
//3-> t t t t     f     f
//4->                 f   

public:
    int countPrimes(int n) {
        if(n<2) return 0;
        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false;
        for(int i= 2; i<n; ++i){
            if(isPrime[i]){
                for(int j=2; i*j<n; ++j){ // j =2 to avoid itself
                    isPrime[i*j] = false;
                }
            }
        }
        int sum = 0;
        for(int i=0; i<n; ++i){
            if(isPrime[i]) ++sum;
        }

        return sum;
    }
};
