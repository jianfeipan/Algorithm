#include "pch.h"
#include <iostream>
#include <stack>


#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/*
Input: array = [-8, 3, -5, 1, 51, 56, 0, -5, 29, 43, 78, 75, 32, 76, 73, 76], 
ranges = [[5, 8], [10, 13], [3, 6], [20, 25]]
Output: [-8, -5, 1, 51, 56, 0, -5, 29, 43, 78, 75, 32, 76, 73, 76]


can rangegs have loverlapping ? yes
can have duplicated in array ? yes
ranges are all validated -> first<=second
range of values in array ? INT_MIN - MINT_MAX
ranges close open? : >= or >


*/
static bool inRanges(int num, const vector<pair<int, int>> & ranges)
{
   for (const auto & range : ranges)
   {
      if (range.first <= num && range.second >= num) return true;
   }
   return false;
}


vector<int> cleanArray_brute_force(const vector<int>& nums, const vector<pair<int, int>> & ranges )
{
   /*
   idea : check one by one, if in range
   M ranges
   N nums

   O(N*M)


   */
   vector<int> cleaned;
   for (int num : nums)
   {
      if (!inRanges(num, ranges))
      {
         cleaned.push_back(num);
      }
   }

   return cleaned;
}

vector<int> cleanArray_hash_set(const vector<int>& nums, const vector<pair<int, int>> & ranges)
{
   /*
   idea: where do we repeat : 
   1. ranges overlapping : we can reduce that to reduce the ranges number to compare
   2. range is not well organized : a BST like range tree ?  
   3 .or read rang in to a hashset --> if ranges are small 

   S: O(N)
   T: O(N+M*L)

   */
   vector<int> cleaned;

   unordered_set<int> toBeremoved;

   for (const auto & range : ranges)
   {
      for (int i = range.first; i <= range.second; ++i)
      {
         toBeremoved.insert(i);
      }
   }

   for (int num : nums)
   {
      if (!toBeremoved.count(num)) cleaned.push_back(num);
   }
   return cleaned;
}



vector<int> cleanArray(const vector<int>& nums, const vector<pair<int, int>> & ranges)
{
   return cleanArray_hash_set(nums, ranges);
}

int main()
{
   const auto & cleanedArray = cleanArray({ -8, 3, -5, 1, 51, 56, 0, -5, 29, 43, 78, 75, 32, 76, 73, 76 }, { {5, 8},{10, 13},{3, 6},{20, 25} });

   for (const auto & num : cleanedArray) cout << num << ", ";

   return 0;
}
