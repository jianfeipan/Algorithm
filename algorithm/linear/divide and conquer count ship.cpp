/*
Question:
Consider the sea to be a cartesian plane. 
There are ships at different places in the sea. 
Given two points, which are the top right and bottom left corners of a rectangle, find the number of ships present in between the two points 
(more specifically, ships present inside the rectangle formed by these two points).

You have a function 
hasShips(A: Point, B: Point) -> 
bool which takes two Points as arguments and returns a boolean. 
If there are ships in between the two points, it returns true, else false.
If you want to check whether a ship is present at a point, say A(2, 2), 
you can pass the same point twice into the function above as so: hasShips(A, A) which returns true if there's a ship at point A, and aliter.
The Point class looks like:

class Point():
   def __init__(self, x, y):
      self.x = x
      self.y = y
NOTE: The interviewer specifically asked to start checking from bottom to top.

*/


#include "pch.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

//input
using Point = pair<int, int>;
bool hasShips(const vector<vector<int>> & map, Point a, Point b)
{
   for (size_t i = a.first; i <= b.first; ++i)
   {
      for (size_t j = a.second; j <= b.second; ++j)
         if (map[i][j] == 1) return true;
   }
   return false;
}


int countShips(const vector<vector<int>> & map, Point a, Point b)
{
   cout << a.first<<"," <<a.second<< " - " << b.first<<"," << b.second<<endl;
   if (a.first > b.first || a.second > b.second) return 0;
   if (!hasShips(map, a, b)) return 0;

   if (a.first == b.first && a.second == b.second)
      return 1;

   int linMid = (a.first + b.first) >> 1;
   int colMid = (a.second+ b.second) >> 1;

   return countShips(map, a, {linMid, colMid})
      + countShips(map, {a.first, colMid+1}, {linMid, b.second})
      + countShips(map, {linMid+1, a.second}, {b.first, colMid })
      + countShips(map, {linMid+1, colMid+1}, b);

   //T(N) =4 *  T(N/4) + O(1) ==> O(logN)
}



int main()
{
   vector<vector<int>> map({
      {1,0,0,1,0,1,0,1,1,1,0},
      {1,0,0,1,0,1,0,1,1,1,0},
      {0,0,1,0,1,0,1,1,1,0,0},
      {0,1,0,1,0,1,1,1,0,0,0}
   });

   cout << "shifcount : " << countShips(map, { 0,0 }, {3,4}) << endl;


   return 0;
}
