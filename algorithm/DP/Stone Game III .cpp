/*
Stone Game III

Alice and Bob are playing a game with piles of stones.
There are several stones arranged in a row,
and each stone has an associated value which is an integer given in the array stoneValue.

Alice and Bob take turns, with Alice starting first.
On each player's turn, that player can take 1, 2, or 3 stones
from the first remaining stones in the row.

The score of each player is the sum of the values of the stones taken.
The score of each player is 0 initially.

The objective of the game is to end with the highest score,
and the winner is the player with the highest score and there could be a tie.
The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return "Alice" if Alice will win,
"Bob" if Bob will win,
or "Tie" if they will end the game with the same score.

Example 1:

Input: stoneValue = [2,4,3,1]

Output: "Alice"
Explanation: In first move,
Alice will pick the first three stones (2,4,3)
and in the second move Bob will pick the last remaining stone (1).
The final score of Alice is (2 + 4 + 3 = 9) which is greater than the Bob's score (1).

Example 2:

Input: stoneValue = [1,2,1,5]

Output: "Bob"
Explanation: In first move, Alice will pick the first three stones (1,2,1)
and in the second move Bob will pick the last remaining stone (5).
The final score of Alice is (1 + 2 + 1 = 4) which is lesser than the Bob's score (5).

Example 3:

Input: stoneValue = [5,-3,3,5]

Output: "Tie"
Explanation: In first move,
Alice will pick the first three stones (5,-3,3)
and in the second move Bob will pick the last remaining stone (5).
The final score of Alice is (5 + -3 + 3 = 5)
which is equal to the Bob's score (5).

Constraints:

1 <= stoneValue.length <= 50,000
-1000 <= stoneValue[i] <= 1000

*/


/*
Greedy may not give the optimal:
[1 1 1 1 5]
Alice should take only 1 in the first round

a better solution could be DP:

    aliceTurn(from, stones)
        max{
            stones[from] + bobTurn(from+1, stones) // take 1
            stones[from]+.. + bobTurn(from+2, stones) // take 2
            stones[from]+ .. + bobTurn(from+3, stones) // take 3
        }
    bobTurn(){
        similar
    }

*/
#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;
    vector<int> suffixSum;

    // max score the current player can get from index i onward
    int maxFrom(int i, const vector<int>& stones) {
        if(i >= (int)stones.size()) return 0;
        if(memo.count(i)) return memo[i];

        int best = INT_MIN;
        int taken = 0;
        for(int k = 1; k <= 3 && i + k - 1 < (int)stones.size(); ++k){
            taken += stones[i + k - 1];
            best = max(best, taken + suffixSum[i + k] - maxFrom(i + k, stones));
        }
        return memo[i] = best;
    }

public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        suffixSum.assign(n + 1, 0);
        for(int i = n - 1; i >= 0; --i)
            suffixSum[i] = suffixSum[i + 1] + stoneValue[i];

        memo.clear();
        int aliceScore = maxFrom(0, stoneValue);
        int bobScore = suffixSum[0] - aliceScore;

        if(aliceScore == bobScore) return "Tie";
        if(aliceScore > bobScore) return "Alice";
        return "Bob";
    }
};
