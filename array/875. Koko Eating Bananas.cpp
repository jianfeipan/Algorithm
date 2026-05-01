/*
You are given an integer array piles where piles[i] is the number of bananas in the ith pile. You are also given an integer h, which represents the number of hours you have to eat all the bananas.

You may decide your bananas-per-hour eating rate of k. Each hour, you may choose a pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, you may finish eating the pile but you can not eat from another pile in the same hour.

Return the minimum integer k such that you can eat all the bananas within h hours.

Example 1:

Input: piles = [1,4,3,2], h = 9

Output: 2
Explanation: With an eating rate of 2, you can eat the bananas in 6 hours. With an eating rate of 1, you would need 10 hours to eat all the bananas (which exceeds h=9), thus the minimum eating rate is 2.

Example 2:

Input: piles = [25,10,23,4], h = 4

Output: 25
Constraints:

1 <= piles.length <= 1,000
piles.length <= h <= 1,000,000
1 <= piles[i] <= 1,000,000,000

*/

class Solution {

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        
        auto time = [&piles](int rate){
            int t = 0;
            for(auto pile : piles){
                t += ceil(static_cast<double>(pile) / rate);
            }
            return t;
        };

        int l = 0;
        int r = *max_element(piles.begin(), piles.end())+1;

        while(l+1!=r){
            auto m = l+(r-l)/2;
            if(time(m) <= h) r=m; 
            // in a normal binary search, we do l=m when is_blue, that's because
            // number going right is going bigger.
            // but here when m going bigger, the time is going smaller, so we do r=m when is_blue
            else l=m;
        }

        return r;
    }
};

