/*

490. The Maze
Problem Description: 
There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). 
The ball can go through the empty spaces by rolling up, down, left, or right, 
but it won't stop rolling until it hits a wall. 
When the ball stops, it could choose the next direction.

Given the m * n maze, the ball's start position, and the destination, 
where start = [start_row, start_col] 
and destination = [destination_row, destination_col], 
return true if the ball can stop at the destination, 
otherwise return false.
Constraints 
  & RulesThe ball cannot stop in the middle of a path: It only stops when it hits a wall or the boundary of the maze.
  The destination is a "stop": You only return true if the ball can land exactly on the destination coordinates 
  after it finishes a roll.
  Passing through the destination while rolling does not count.
*/



#include <iostream>
#include <vector>
#include <queue>

using namespace std;
constexpr array<array<int, 2>, 4> DIRECTIONS{{
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
}};
class Solution {
public:
    /**
     * @param maze: the maze grid
     * @param start: starting coordinates [row, col]
     * @param destination: target coordinates [row, col]
     * @return: true if the ball can stop at the destination
     */
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        const auto R = maze.size();
        const auto C = maze[0].size();
        // BFS
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        maze[start[0]][start[1]]=2; // visited
        while(!q.empty()){
            auto [r, c] = q.front(); q.pop();
            if(r == destination[0] && c == destination[1]) return true;

            for(const auto& direction : DIRECTIONS){
                int newR = r;
                int newC = c;
                bool moved=false;
                while( newR>=0 && newR<R
                    && newC>=0 && newC<C
                    && maze[newR][newC]!=1 ){

                    newR+=direction[0];
                    newC+=direction[1];
                    moved=true;
                }
                if(moved){
                    newR-=direction[0];
                    newC-=direction[1];
                }

                if(maze[newR][newC]!=2){
                    maze[newR][newC]=2;
                    q.push({newR, newC});
                }
            }
        }


        return false;
    }
};

// --- Test Suite ---
void runTest(int id, vector<vector<int>> maze, vector<int> start, vector<int> dest, bool expected) {
    Solution sol;
    bool result = sol.hasPath(maze, start, dest);
    cout << "Test " << id << ": " << (result == expected ? "PASSED ✅" : "FAILED ❌")
         << " (Expected: " << (expected ? "true" : "false") << ", Got: " << (result ? "true" : "false") << ")" << endl;
}

int main() {
    // Test 1: Standard reachable path
    runTest(1,
        {
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 1, 0},
          {1, 1, 0, 1, 1},
          {0, 0, 0, 0, 0}},
          {0, 4}, {4, 4}, true);

    // Test 2: Unreachable path (blocked by walls)
    runTest(2,
        {
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 1, 0},
          {1, 1, 0, 1, 1},
          {0, 0, 0, 0, 0}},
          {0, 4}, {3, 2}, false);

    // Test 3: Simple straight line
    runTest(3,
        {{0, 0, 0},
         {0, 1, 0},
         {0, 0, 0}},
        {0, 0}, {0, 2}, true);

    return 0;
}
