/*
You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.

Return the number of distinct combinations that total up to amount. If it's impossible to make up the amount, return 0.

You may assume that you have an unlimited number of each coin and that each value in coins is unique.

Example 1:

Input: amount = 4, coins = [1,2,3]

Output: 4
Explanation:

1+1+1+1 = 4
1+1+2 = 4
2+2 = 4
1+3 = 4
Example 2:

Input: amount = 7, coins = [2,4]

Output: 0
Constraints:

1 <= coins.length <= 100
1 <= coins[i] <= 5000
0 <= amount <= 5000
*/

/*
ideas: amount = 4, coins = [1,2,3]
   take 1 [1] 3[2, 3] ->1
   take 2 [1] 2[2, 3]->1
   take 3 [1] 1[2 ,3]->0
   take 4 [1] ->1 
    
    DP recursive: topdown sue 1, .... [1] solutions for f(rest, [2...)

*/
class Solution {
private:
    int changeFrom(int amount, int from, 
                const vector<int>& coins, 
                unordered_map<int, int>& memory){
        if(amount == 0) return 1;
        if(from == coins.size()) return 0;

        const auto key = 100*amount+from; // coins size is <=100 :  from is [0,99]
        if(memory.count(key)) return memory[key];

        int solutions = 0; 

        const auto& currentCoin = coins[from];
        int restAmount = amount;
        while(restAmount >= 0){
            solutions += changeFrom(restAmount, from+1, coins, memory);
            restAmount -= currentCoin;
        }

        return memory[key] = solutions;
    }
public:
    int change(int amount, vector<int>& coins) {
        unordered_map<int, int> memory;
        return changeFrom(amount, 0, coins, memory);

    }
};
