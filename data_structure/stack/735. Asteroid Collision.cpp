/*

735. Asteroid Collision

We are given an array asteroids of integers representing asteroids in a row. The indices of the asteroid in the array represent their relative position in space.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

 

Example 1:

Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
Example 2:

Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
Example 3:

Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
Example 4:

Input: asteroids = [3,5,-6,2,-1,4]​​​​​​​
Output: [-6,2,4]
Explanation: The asteroid -6 makes the asteroid 3 and 5 explode, and then continues going left. On the other side, the asteroid 2 makes the asteroid -1 explode and then continues going right, without reaching asteroid 4.

*/

class Solution {
/*
idea:
       i  j
    [3,5,-6,2,-1,4]​​​​​​​

    [3, 5]-> -6
    res[-6]
    [2] -> -1
    [2,4]
    res [-6, 2, 4]

    - using a stack: to put all asteroids moving to the right, 
    - when meet a asteroids to left, pop until a bigger one
O(N)
*/    
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> finalState;
        vector<int> movingRight; // stack
        for(const auto& asteroid : asteroids){
            if(asteroid>0) movingRight.push_back(asteroid);
            else{
                while(!movingRight.empty() 
                    && movingRight.back()<(-1*asteroid)){
                    movingRight.pop_back();// explored by the current negative
                }

                if(movingRight.empty()){ // no more, the current negative can stay in the final
                    finalState.push_back(asteroid);
                }else{
                    if(movingRight.back() == (-1*asteroid)){ // same size: both explored
                        movingRight.pop_back();
                    }
                }
            }
        }

        finalState.insert(finalState.end(),movingRight.begin(), movingRight.end());

        return finalState;
    }
};
