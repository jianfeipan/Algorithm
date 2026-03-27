/*
You are given a stream of points consisting of x-y coordinates on a 2-D plane. Points can be added and queried as follows:

Add - new points can be added to the stream into a data structure. Duplicate points are allowed and should be treated as separate points.
Query - Given a single query point, count the number of ways to choose three additional points from the data structure such that the three points and the query point form a square. The square must have all sides parallel to the x-axis and y-axis, i.e. no diagonal squares are allowed. Recall that a square must have four equal sides.
Implement the CountSquares class:

CountSquares() Initializes the object.
void add(int[] point) Adds a new point point = [x, y].
int count(int[] point) Counts the number of ways to form valid squares with point point = [x, y] as described above.
*/

/*

what data structure do we need?
    -> how we count squares
       given q, I need to know all points on the same x and y
    -> unordered_map<X, unordered_map<Y, count>>
    and unordered_map<Y, unordered_map<X, count>>




      0 1 2 3 4 5
0       *   * *
1           * *
2       *   q * 
3           * *
4           *

given Q[r, c] 2,3
    allpoints on r:  (2,1) (2,4)
    allpointts on c   0,3  1,3   3,3  4,3 

take the longer one 0,3  1,3   3,3  4,3
check if we have sqaure with 2,3 and 0,3 -> need 2,1  0,1 
the number will be each points count multiplied together
*/

#include<array>

class CountSquares {
private:
    using R = int;
    using C = int;
    unordered_map<R, unordered_map<C, int>> rcCount;
    

public:
    CountSquares() {
        
    }
    
    void add(vector<int> point) {
        ++rcCount[point[0]][point[1]];
    }
    
    int count(vector<int> point) {
        const int r = point[0];
        const int c = point[1];

        int res = 0;

        for(auto& [nextC, count] : rcCount[r]){
            // looking for square with
            // [r, c]  and [r, nextC]
            int side = abs(nextC-c);
            if(side>0){
                // look for
                // down [r+side, c] [r+side, nextC]
                // up [r-side, c] [r-side, nextC]
                static array<int, 2> SIGN = {1, -1};
                for(int sign : SIGN){
                    int nextR = r + sign * side;
                    if(rcCount.count(nextR))
                    {
                        if(rcCount[nextR].count(c) && rcCount[nextR].count(nextC)){
                            res += count * rcCount[nextR][c] * rcCount[nextR][nextC];
                            
                        }
                    }
                }
            }
        }

        return res;

    }
};
