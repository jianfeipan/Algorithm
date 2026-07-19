/*
   Input: "aaabbbc"
Output: "c"
Explanation:
1. Remove 3 'a': "aaabbbbc" => "bbbbc"
2. Remove 4 'b': "bbbbc" => "c"

Example 2:
Input: "aabbbacd"
Output: "cd"
Explanation:
1. Remove 3 'b': "aabbbacd" => "aaacd"
2. Remove 3 'a': "aaacd" => "cd"

Example 3:
Input: "aabbccddeeedcba"
Output: ""
Explanation:
1. Remove 3 'e': "aabbccddeeedcba" => "aabbccdddcba"
2. Remove 3 'd': "aabbccdddcba" => "aabbcccba"
3. Remove 3 'c': "aabbcccba" => "aabbba"
4. Remove 3 'b': "aabbba" => "aaa"
5. Remove 3 'a': "aaa" => ""

Example 4:
Input: "aaabbbacd"
Output: "acd"
Explanation:
1. Remove 3 'a': "aaabbbacd" => "bbbacd"
2. Remove 3 'b': "bbbacd" => "acd"

I solved it with recursion and also discussed the stack based approach.
Follow-up:
What if you need to find the shortest string after removal?
Example:
Input: "aaabbbacd"
Output: "cd"
Explanation:
1. Remove 3 'b': "aaabbbacd" => "aaaacd"
2. Remove 4 'a': "aaaacd" => "cd"

"abbbaaabb" 
---> if remove b then remove a : bb
---> if remove a then remove b : a


*/
#include "pch.h"
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;



string removeDuplicates(string s, int k)//remove exactly k duplicated, the k+ 1 th will be kept
{
   vector<pair<char, size_t>> left;
   for (char c : s)
   {
      if (left.empty() || left.back().first != c)
      {
         left.push_back({ c, 1 });
      }
      else
      {
         left.back().second++;
         if (left.back().second == k)
         {
            left.pop_back();
         }
      }
   }

   stringstream ss;
   for(const auto & chars : left)
   {
      ss << string(chars.second, chars.first);
   }
   return ss.str();
}

string candyCrash(string s)
{
   return removeDuplicates(s, 3);
}



static void bestCandyCrush(string& s,
   string& crushedMask,
   int crushedCounter,
   string& bestResult,
   unordered_set<string>& evaluated)
{
   //cout << "visit : " << bestResult << endl;
   //cout << "mask  : " << crushedMask << endl;

   // VISITED : if the mask was already evaluated, we already have the best
   // result for this recursive path
   if (evaluated.find(crushedMask) != evaluated.end())
      return;

   //if in this recusion, the input mask (with crushedCounter) makes a better result
   if (s.length() - crushedCounter < bestResult.length())
   {
      bestResult = "";

      for (int i = 0; i < s.length(); ++i)
      {
         if (crushedMask[i] == '.')
            bestResult += s[i];
      }
   }

   // try to find some more candies to crush
   
   auto tryAndBackTrack = [&](const vector<int> & currentSameLetters)
   {
      // remove the new crushed group
      for (int move : currentSameLetters)
         crushedMask[move] = 'X';

      // recursion with the new changes!!!!!!!
      bestCandyCrush(s,
         crushedMask,
         crushedCounter + currentSameLetters.size(),
         bestResult,
         evaluated);

      // backtrack!!!!!!!!!!!!!!!!!!
      for (int move : currentSameLetters)
         crushedMask[move] = '.';
   };

   char current = 0;
   vector<int> currentSameLetters;

   //from left to right, find all possible >=3 letters and create branches : "tryAndBackTrack"
   for (int i = 0; i < s.length(); ++i)
   {
      if (crushedMask[i] == '.')
      {
         if (s[i] == current)
         {
            currentSameLetters.push_back(i);
         }
         else
         {
            if (currentSameLetters.size() >= 3)
            {
               tryAndBackTrack(currentSameLetters);
            }
            current = s[i];
            currentSameLetters.clear();
            currentSameLetters.push_back(i);
         }
      }
   }

   //the last letter should be count too
   if (currentSameLetters.size() >= 3)
   {
      tryAndBackTrack(currentSameLetters);
   }

   //Mark solution visited
   evaluated.insert(crushedMask);
}


string bestCandyCrush(string s) 
{

   string crushedMask(s.length(), '.');
   string bestResult = s;

   unordered_set<string> evaluated;

   bestCandyCrush(s, crushedMask, 0, bestResult, evaluated);

   return bestResult;
}


int main()
{
   vector<string> tests =
   {
      "aaabbbc",
      "aabbbacd",
      "aabbccddeeedcba",
      "aaabbbacd"
   };

   for (const auto & test : tests)
   {
      cout << test << "->" << candyCrash(test) << endl;
   }

   vector<string> bestTests =
   {
      "aaabbbc",
      "aabbbacd",
      "aabbccddeeedcba",
      "aaabbbacd",
      "abbbaaabb"
   };

   for (const auto & test : bestTests)
   {
      cout << test << "--best solution ->" << bestCandyCrush(test) << endl;
   }

}
