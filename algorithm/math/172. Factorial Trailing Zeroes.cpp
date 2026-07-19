class Solution {


    /*
    
    Given an integer n, return the number of trailing zeroes in n!. (factorial)

Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
    

    Input: n = 5
Output: 1
Explanation: 5! = 120, one trailing zero.




Fact: 
    1 n! could be very big , surpass INT_MAXX

Idea:
    let's write down :
        1! = 1
        2! = 2
        3! = 6 
        4! = 24
        5! = 120
        6! = 720
        7! = 7*720
        8! = 8*7!

    recursive.
correct: 

    from 1 - 10, only 1*10 or 2* 5 could generate a 10, then it's the same thing for next digit
    so from 1 - n, we need to know how many [2,5] and [1, 10]
    */

private:

    int factorial(int n){
        if(n ==1) return 1;
        return  factorial(n-1);
    }

    unsigned long long trailingZeroesHelper(int n, int & zeros){
        if(n <= 1) return 1;

        unsigned long long nextLeft = n*trailingZeroesHelper(n-1, zeros); //--> overflow enven unsigned longlong
        cout<<n << ":" <<nextLeft<<endl;
        while(nextLeft%10 == 0)
        {
            cout<<zeros<<endl;
            nextLeft/=10;
            ++zeros;
        }

       
        return nextLeft;
        
    }


public:
    int trailingZeroes_overflow(int n) {
        int zeros = 0;
        auto last = trailingZeroesHelper(n, zeros);
        while(last%10 == 0)
        {
            last/=10;
            ++zeros;
        }
        return zeros;
    }

    int trailingZeroes(int n) {
        int ans=0;
        while(n>0){
            ans+=n/5;
            n/=5;
        }
        return ans;
    }
};
