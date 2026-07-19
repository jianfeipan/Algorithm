

/*

Given an int n. You can use only 2 operations:

multiply by 2
integer division by 3 (e.g. 10 / 3 = 3)
Find the minimum number of steps required to generate n from 1.

Example 1:

Input: 10
Output: 6
Explanation: 1 * 2 * 2 * 2 * 2 / 3 * 2
6 steps required, as we have used 5 multiplications by 2, and one division by 3.
Example 2:

Input: 3
Output: 7
Explanation: 1 * 2 * 2 * 2 * 2 * 2 / 3 / 3
7 steps required, as we have used 5 multiplications by 2 and 2 divisions by 3.


followup : how to now the path
*/

#include "pch.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
template<typename T>
static void print(const std::vector<T> & v)
{
   std::cout << "[ ";
   for (const T & t : v)
      std::cout << t << ' ';
   std::cout << "]" << std::endl;;
}

static int minStepGenerate_BFS(int num)
{
   /*
   Idea : generate numbers from 1 with all pathes
            - use BFS to test if we have the target number in my depth : this depth is the min step number
            - improvement : use a vector<bool>[N] or a set to  cache and avoid recomputations
   */
   queue<pair<int, vector<int>>> q_withPathes;
   q_withPathes.push({ 1, {1} });
   int minStep = 0;
   unordered_set<int> cache;

   while (!q_withPathes.empty())
   {
      auto size = q_withPathes.size();
      for (size_t i = 0; i < size; ++i)
      {
         auto current = q_withPathes.front(); q_withPathes.pop();
         if (current.first == num)
         {
            cout << "path : ";
            print(current.second);
            return minStep;
         }
         
         if(cache.find(current.first * 2) == cache.end())
         {
            vector<int> path2(current.second);
            path2.push_back(2);
            q_withPathes.push({ current.first * 2, path2 });
         }

         if (cache.find(current.first /3) == cache.end())
         {
            vector<int> path3(current.second);
            path3.push_back(3);
            q_withPathes.push({ current.first / 3, path3 });
         }
      }
      ++minStep;
   }
   return -1;
}



int minStepGenerate(int num)
{
   return minStepGenerate_BFS(num);
}


int main()
{
   int testCases[] = {10, 3};
   for(int num : testCases)
      cout <<"minstep : "<<num<< " : "<< minStepGenerate(num) << endl;

   return 0;
}
