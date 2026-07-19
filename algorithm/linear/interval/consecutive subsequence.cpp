

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Longest Consecutive Subsequence
Difficulty Level : Medium

Given an array of integers, find the length of the longest sub-sequence such that elements in the subsequence are consecutive integers, the consecutive numbers can be in any order. 

Examples:  

Input: arr[] = {1, 9, 3, 10, 4, 20, 2}
Output: 4
Explanation: 
The subsequence 1, 3, 4, 2 is the longest 
subsequence of consecutive elements

Input: arr[] = {36, 41, 56, 35, 44, 33, 34, 92, 43, 32, 42}
Output: 5
Explanation: 
The subsequence 36, 35, 33, 34, 32 is the longest 
subsequence of consecutive elements.


followup what if we have repeated numbers? 
use a tree set to keep unique, if not, we will have deuplicated after sort
*/


vector<int> longestConsecutiveSubsequence_sort(const vector<int>& nums) 
{
    vector<int> sorted(nums);
    sort(sorted.begin(), sorted.end());
    
    int maxConsecutiveCount = 0;
    size_t maxStart = 0;
    size_t maxEnd = 0;
    int consecutiveCount = 0;
    for(size_t i = 0; i<sorted.size(); ++i)// 1 2 3 5 7 8 9 
    {
        if(i<sorted.size()-1 && sorted[i+1] - sorted[i] == 1)
        {
            ++consecutiveCount;
        }
        else
        {
            if(maxConsecutiveCount < consecutiveCount+1)
            {
                maxConsecutiveCount = consecutiveCount+1;
                maxEnd = i;
                maxStart = i-consecutiveCount;
                consecutiveCount = 0;
            }
        }
    }
    
    return vector<int>(sorted.begin()+maxStart, sorted.begin()+maxEnd+1);
}

vector<int> longestConsecutiveSubsequence(const vector<int>& nums) 
{
    return longestConsecutiveSubsequence_sort(nums);
}


int main(int argc, char *argv[])
{
   auto subsequence = longestConsecutiveSubsequence({36, 41, 56, 35, 44, 33, 34, 92, 43, 32, 42});
   
   for(auto num : subsequence) cout<< num<<", ";
   cout<<endl;
   return 0;
}
