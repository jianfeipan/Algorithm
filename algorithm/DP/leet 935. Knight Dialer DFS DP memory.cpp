/*
The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:

A chess knight can move as indicated in the chess diagram below:

We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
123
456
789
*0#

Given an integer n, return how many distinct phone numbers of length n we can dial.

You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.

As the answer may be very large, return the answer modulo 109 + 7.

 

Example 1:

Input: n = 1
Output: 10
Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
Example 2:

Input: n = 2
Output: 20
Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
Example 3:

Input: n = 3131
Output: 136006598
Explanation: Please take care of the mod.

*/
static constexpr int MOD = 1e9 + 7;
static const vector<vector<int>> NEXT{
    {4, 6},//0
    {6, 8},//1
    {7, 9},//2
    {4, 8},//3
    {0, 3, 9},//4
    {},//5
    {0, 1, 7},//6
    {2, 6},//7
    {1, 3},//8
    {2, 4}//9
};
class Solution {
private:
    
    int knightDialerFrom(int i, int step, vector<vector<int>>& cache){
        if(step == 0) return 1;

        auto& count = cache[i][step];
        if(count!=-1) return count;

        int sum=0;
        for(int next : NEXT[i]){
            sum += knightDialerFrom(next, step-1, cache)% MOD;
            sum %= MOD;
        }
        return count = sum;
    }
public:
    int knightDialer(int n) {
        int totalDial=0;
        vector<vector<int>> cache(10, vector<int>(n, -1));
        for(int i = 0; i<=9; ++i){
            totalDial += knightDialerFrom(i, n-1, cache)% MOD;
            totalDial %= MOD;
        }
        return totalDial;
    }
};
