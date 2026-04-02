/*
an array and two int x, y.
every operation: pick one element, subtract x from it and subtract y from other element, once an element hits zero, any further subtractions are wasted.
determine the minimum operations to reduce all elements to zero or negative



*/

#include <bits/stdc++.h>
using namespace std;

long long min_operations(const vector<long long>& arr, long long x, long long y) {
    auto feasible = [&](long long k) -> bool {
        if (x > y) {
            long long extra = x - y;
            long long need = 0;
            for (long long a : arr) {
                long long remain = a - k * y;
                if (remain > 0) {
                    need += (remain + extra - 1) / extra;
                    if (need > k) return false;
                }
            }
            return need <= k;
        } 
        else if (x == y) {
            for (long long a : arr) {
                if (a > k * y) return false;
            }
            return true;
        } 
        else { // x < y
            long long diff = y - x;
            long long total_cap = 0;
            for (long long a : arr) {
                if (a > k * y) return false; // even x==y, we need at least a==ky, now x is small, we need more.
                // every time being picked, we are missing to remove diff(y-x)
                // if a is picked c times, we should have: a - k*y + c*diff <=0  : c<= (k*y-a)/diff
                // and the sum of c should is k! 
                // so  accumulated c(k) <= total_cap = sum((k*y-a)/diff)
                total_cap += (k * y - a) / diff;
                
                if (total_cap >= k) return true;
            }
            return total_cap >= k;
        }
    };

    long long lo = -1, hi = 2;// -1 , N
    while (!feasible(hi)) hi *= 2;

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (!feasible(mid)) lo = mid; // is blue
        else hi = mid;
    }
    return hi;
}
