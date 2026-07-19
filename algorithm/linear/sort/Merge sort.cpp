#include "pch.h"
#include <iostream>
#include <utility>
#include <vector>


static void print(const std::vector<std::pair<int, int>> & v)
{
   std::cout << "[ ";
   for (const auto & t : v)
      std::cout << " [" <<t.first <<","<<t.second << "], ";
   std::cout << "]" << std::endl;;
}

template<typename T>
static void print(const std::vector<T> & v)
{
   std::cout << "[ ";
   for (const auto & t : v)
      std::cout << t << ' ';
   std::cout << "]" << std::endl;;
}


static void merge(std::vector<int> & s, int from, int mid, int to)
{
   std::vector<int> merged(to - from + 1, 0);
   int left = from;
   int right = mid + 1;
   int mergedIndex = 0;

   while (left <= mid && right <= to)
   {
      if (s[left] <= s[right])
      {
         merged[mergedIndex] = s[left];
         ++left;
      }
      else
      {
         merged[mergedIndex] = s[right];
         right++;
      }
      ++mergedIndex;
   }
   //rest of left or right
   while (left <= mid)
   {
      merged[mergedIndex] = s[left];
      ++left;
      ++mergedIndex;
   }

   while (right <= to)
   {
      merged[mergedIndex] = s[right];
      ++right;
      ++mergedIndex;
   }

   //put merged into original
   for (int i = 0; i < merged.size(); ++i)
   {
      s[i + from] = merged[i];
   }
   std::cout << "merged : " << std::endl;
   print(merged);
}

static void process_merge_sort(std::vector<int> & s, int from, int to)
{
   if (from >= to)
      return;

   int mid = (from + to) / 2; //>>1
   process_merge_sort(s, from, mid);
   process_merge_sort(s, mid + 1, to);
   merge(s, from, mid, to);
}

void merge_sort(std::vector<int> & s)
{
   process_merge_sort(s, 0, s.size() - 1);
}


/*
merge sort can be a solution for another problem : smaller sum :

given a vector, every elemnt 's  left has its elements smaller than this element, how to summ them all ?

example :
{2,5,3,1,4}
2--> left smaler : null
5--> left smaller : 2
3--> 2
1--> null
4--> 2,3,1

result = 2 + 2 + 2+3+1

idea: smaller element sum on left, we can transform it to find N number on right is bigger than me, so current element will be sumed N times

by merge sort, in the merge step, we are comparing left and right element, and we can know how many bigger than me on right


*/
static int mergeSmallerSum(std::vector<int> & s, int from, int mid, int to)
{
   int sum = 0;

   std::vector<int> merged(to - from + 1, 0);
   int left = from;
   int right = mid + 1;
   int mergedIndex = 0;

   while (left <= mid && right <= to)
   {
      if (s[left] < s[right])
      {
         merged[mergedIndex] = s[left];
         //small sum is produced when we merge
         //left smaller than right, so this left element should be sumed N times where N is the number of element bigger than left, which is to-right+1
         sum += (to - right + 1) * s[left];
         ++left;
      }
      else
      {
         merged[mergedIndex] = s[right];
         right++;

      }
      ++mergedIndex;
   }
   //rest of left or right
   while (left <= mid)
   {
      merged[mergedIndex] = s[left];
      ++left;
      ++mergedIndex;
   }

   while (right <= to)
   {
      merged[mergedIndex] = s[right];
      ++right;
      ++mergedIndex;
   }

   //put merged into original
   for (int i = 0; i < merged.size(); ++i)
   {
      s[i + from] = merged[i];
   }
   return sum;
}

static int processSmallerSum(std::vector<int> & nums, int from, int to)
{

   if (from >= to)
      return 0;

   const int mid = (from + to) / 2; //>>1
   int leftSum = processSmallerSum(nums, from, mid);
   int rightSum = processSmallerSum(nums, mid + 1, to);
   int mergSum = mergeSmallerSum(nums, from, mid, to);

   return leftSum + rightSum + mergSum;
}

int smallerSum(std::vector<int> & nums)
{
   return processSmallerSum(nums, 0, nums.size() - 1);
}


/*
merge sort can be a solution for another problem : decending pair

given a vector, find all pairs decending from left to right

example :
{2,5,3,1,4}
2--> decending pair : [2,1]
5--> [5,3][5,1][5,4]
3--> [3,1]
1--> null
4--> null
we can use merge

*/
static void mergeForDecendingPair(std::vector<int> & s, int from, int mid, int to, std::vector<std::pair<int, int>> & decendingPairs)
{

   std::vector<int> merged(to - from + 1, 0);
   int left = from;
   int right = mid + 1;
   int mergedIndex = 0;

   while (left <= mid && right <= to)
   {
      if (s[left] <= s[right])//equals to be here to make bigger left count the right one: example : merge([2,5], [2,3]) --> 2==2 we need to left++ to make the 5 compare to right 2
      {
         merged[mergedIndex] = s[left];
         ++left;
      }
      else
      {
         //s[left]> s[right] : decending pair, since left is sorted, all elements after left is bigger than s[right]
         for (int i = left; i <= mid; ++i)
         {
            decendingPairs.emplace_back(s[i], s[right]);
         }
         merged[mergedIndex] = s[right];
         right++;

      }
      ++mergedIndex;
   }
   //rest of left or right
   while (left <= mid)
   {
      merged[mergedIndex] = s[left];
      ++left;
      ++mergedIndex;
   }

   while (right <= to)
   {
      merged[mergedIndex] = s[right];
      ++right;
      ++mergedIndex;
   }

   //put merged into original
   for (int i = 0; i < merged.size(); ++i)
   {
      s[i + from] = merged[i];
   }

}

static void processDecendingPair(std::vector<int> & nums, int from, int to, std::vector<std::pair<int, int>> & decendingPairs)
{
   if (from >= to)
      return;

   const int mid = (from + to) / 2; //>>1
  processDecendingPair(nums, from, mid, decendingPairs);
  processDecendingPair(nums, mid + 1, to, decendingPairs);
  mergeForDecendingPair(nums, from, mid, to, decendingPairs);
}

std::vector<std::pair<int, int>> decendingPair(std::vector<int> & nums)
{
   std::vector<std::pair<int, int>> decendingPairs;
   processDecendingPair(nums, 0, nums.size() - 1, decendingPairs);
   return decendingPairs;
}

int main()
{
   std::vector<int> nums = { 2,5,3,1,4 };

   print(nums);

   std::cout << "sort : \n";

   //std::cout << smallerSum(nums) << std::endl;
   std::vector<std::pair<int, int>> decendingPairs = decendingPair(nums);


   print(nums);

   print(decendingPairs);

   int i = 1;
   std::cout << i++;


   return 0;

}

