#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
   /**
    * @param grid: the given 2-D world
    * @return: the number of walls
    */

   using Point = pair<int, int>;
   using Region = set<Point>;

   int containVirus(vector<vector<int>> &_grid) {
      //idea: count the infacted region "infecting speed" : how much neighbers will be infected tonight , we always construct the walls for the region who has the highest infecting speed
      //keep in mind : what's the relation of infected number and walls we need : the same.__asm__
      if (_grid.empty() || _grid[0].empty())
         return 0;

      int totalWalls = 0;

      vector<vector<int>> grid(_grid);
      cout << "initial" << endl; log(grid);
      bool goOn = true;
      while (goOn)
      {
         vector<pair<Region, int>> regionWallNeeded = countRegions(grid);
         if (regionWallNeeded.empty())
            return 0;//no infection

        //find the region which need most walls
         int maxWalls = 0;
         int regionIndex = 0;
         for (int i = 0; i < regionWallNeeded.size(); i++)
         {
            if (regionWallNeeded[i].second > maxWalls)
            {
               maxWalls = regionWallNeeded[i].second;
               regionIndex = i;
            }
         }

         //create wall for maxWall's region and the rest will infect
         totalWalls += maxWalls;
         cleanRegion(grid, regionWallNeeded[regionIndex].first);
         cout << "clean" << endl; log(grid);
         //overnight the rest will infact
         bool allCleanOrWeAreDone = infact(grid);
         cout << "infect" << endl; log(grid);
         cout << "stop ? " << allCleanOrWeAreDone << endl;
         goOn = !allCleanOrWeAreDone;

      }
      return totalWalls;
   }

private:
   bool infact(vector<vector<int>> &grid)
   {
      bool haveUninfected = false;
      bool haveInfected = false;
      vector<vector<int>> before(grid);
      for (int lin = 0; lin < before.size(); ++lin)
      {
         for (int col = 0; col < before[0].size(); ++col)
         {
            if (before[lin][col] == 1)
            {
               //cout<<"infect from["<<lin<<","<<col<<"]"<<endl;
               haveInfected = true;
               //visite neigbers
               for (const auto & direction : Directions())
               {
                  int nextLin = lin + direction.first;
                  int nextCol = col + direction.second;

                  if (nextLin >= 0
                     && nextLin < before.size()
                     && nextCol >= 0
                     && nextCol < before[0].size()
                     )
                  {
                     if(before[nextLin][nextCol] == 0)//should infact only 0
                     //cout<<"infect to["<<nextLin<<","<<nextCol<<"]"<<endl;
                        grid[nextLin][nextCol] = 1;
                  }
               }
            }
            else
            {
               haveUninfected = true;
            }
         }
      }
      bool allCleanOrWeAreDone = !haveUninfected || !haveInfected;
      return allCleanOrWeAreDone;
   }

   void cleanRegion(vector<vector<int>> &grid, const Region & region)
   {
      for (const auto & point : region)
      {
         grid[point.first][point.second] = 2;
      }

   }

   vector<pair<Region, int>> countRegions(const vector<vector<int>> &grid)
   {
      vector<pair<Region, int>> regionWallNeeded;
      {//construct and count regions
         vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

         for (int lin = 0; lin < grid.size(); ++lin)
         {
            for (int col = 0; col < grid[0].size(); ++col)
            {
               if (grid[lin][col] == 1 && !visited[lin][col])
               {
                  Region region;
                  int wallsNeeded = 0;
                  visitRegion(lin, col, grid, visited, region, wallsNeeded);
                  regionWallNeeded.push_back({ region, wallsNeeded });
               }
            }
         }
      }
      return regionWallNeeded;
   }

   void visitRegion(int lin, int col, const vector<vector<int>> &grid, vector<vector<bool>> & visited, Region & region, int & count)
   {
      if (grid[lin][col] == 1 && !visited[lin][col])
      {
         visited[lin][col] = true;
         region.insert({ lin, col });
         //visite neigbers
         for (const auto & direction : Directions())
         {
            int nextLin = lin + direction.first;
            int nextCol = col + direction.second;

            if (nextLin >= 0
               && nextLin < grid.size()
               && nextCol >= 0
               && nextCol < grid[0].size()
               )
            {
               if (grid[nextLin][nextCol] == 1)
               {
                  visitRegion(nextLin, nextCol, grid, visited, region, count);
               }
               else if (grid[nextLin][nextCol] == 0)//only uninfacted cells should be protected
               {
                  ++count;
               }
               else
               {
                  //alreay controled zone
               }
            }

         }

      }

   }

   static const vector<pair<int, int>> & Directions()
   {
      const static vector<pair<int, int>> directions({
          {-1, 0},
          { 1, 0},
          { 0,-1},
          { 0, 1}
         });
      return directions;

   }

   void log(const vector<vector<int>> &grid)
   {

      for (int lin = 0; lin < grid.size(); ++lin)
      {
         for (int col = 0; col < grid[0].size(); ++col)
         {
            cout << grid[lin][col] << " ";
         }
         cout << endl;
      }
      cout << endl;

   }

};
