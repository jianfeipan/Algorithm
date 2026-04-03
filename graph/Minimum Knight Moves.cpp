/*
Problem Description:
In an infinite chess board with coordinates -inf +inf,
you have a knight at square $[0, 0]$.
A knight has 8 possible moves it can make,
as illustrated below.
Each move is two squares in a cardinal direction,
then one square in an orthogonal direction.
Return the minimum number of steps needed to move the knight to the square $[x, y]$.
It is guaranteed the answer exists.


*/


#include <iostream>
#include <queue>
#include <unordered_set>
#include <cmath>

using namespace std;

// Encode (x, y) as a single long long for O(1) hashing
struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<long long>()(((long long)p.first << 32) | (unsigned int)p.second);
    }
};

class Solution {
public:
    int minKnightMoves(int targetX, int targetY) {
        // Optimization: Use symmetry to work only in the first quadrant
        targetX = abs(targetX);
        targetY = abs(targetY);

        // Direction offsets for a knight
        static constexpr int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        static constexpr int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

        unordered_set<pair<int,int>, PairHash> visited;
        queue<pair<int,int>> q;

        q.push({0,0});
        visited.insert({0, 0});
        int step = 0;
        while(!q.empty()){
            const int levelSize = q.size();
            for(int j=0; j<levelSize; ++j){

                auto [x, y] = q.front();
                q.pop();
                if(x == targetX && y == targetY) return step;
                for(int i=0; i<8; ++i){
                    auto newX = x+dx[i];
                    auto newY = y+dy[i];
                    if(newX >= -2 && newY >= -2 && newX <= targetX+2 && newY <= targetY+2){
                        pair<int,int> np(newX, newY);
                        if(!visited.count(np)){
                            visited.insert(np);
                            q.push(np);
                        }
                    }
                }
            }
            ++step;
        }
        return step; // Placeholder
    }
};

int main() {
    Solution sol;

    // Test Case 1: Target (2, 1)
    // Expected Output: 1
    cout << "Test Case 1 (2, 1): " << sol.minKnightMoves(2, 1) << " (Expected: 1)" << endl;

    // Test Case 2: Target (5, 5)
    // Expected Output: 4
    cout << "Test Case 2 (5, 5): " << sol.minKnightMoves(5, 5) << " (Expected: 4)" << endl;

    return 0;
}
