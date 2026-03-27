class Solution {
public:
    double myPow(double x, int n) {
        if(n==0) return 1;
        //If x = 0, then n will be positive.
        if(n<0) {
            if(x == 0) return 0; // exception invalid input
            x = 1.0/x; 
            n *= -1;
        }
        double res=1.0;
        for(int i = 0; i < n; ++i){
            res*=x;
        }
        return res;
    }
};


/*
Pow(x, n)
Solved 
Medium
Topics
Company Tags
Hints
Pow(x, n) is a mathematical function to calculate the value of x raised to the power of n (i.e., x^n).

Given a floating-point value x and an integer value n, implement the myPow(x, n) function, which calculates x raised to the power n.

You may not use any built-in library functions.

Example 1:

Input: x = 2.00000, n = 5

Output: 32.00000
Example 2:

Input: x = 1.10000, n = 10

Output: 2.59374
Example 3:

Input: x = 2.00000, n = -3

Output: 0.12500
Constraints:

-100.0 < x < 100.0
-1000 <= n <= 1000
n is an integer.
If x = 0, then n will be positive. */