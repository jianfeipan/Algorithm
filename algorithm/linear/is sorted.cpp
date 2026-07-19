#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>
#include <list>
#include <set>
#include <map>
#include <array>
#include <functional>
#include <algorithm>

using namespace std;

/*

Check if array is sorted or not
Given an array return whether the array is sorted or not (boolean).
true -> Ascending or Descending
true -> if all are same
true -> if just one element
else false


*/


bool isSorted(const vector<int> & nums)//O(N)
{
    if(nums.size()<=1) return true;
    
    bool isIncreasing = nums.front() < nums.back();
    bool isDecreasing = nums.front() > nums.back();
    for(size_t i= 2; i<nums.size(); ++i)
    {
        if(isIncreasing)
        {
             if(nums[i-1] > nums[i])  return false;
        }
        else if(isDecreasing)
        {
            if(nums[i-1] < nums[i]) return false;
        } 
        else
        {
            if(nums[i-1] != nums[i]) return false;
        }
    }
    
    return true;
}

int main()
{
    cout<<isSorted({})<<endl;
    cout<<isSorted({1})<<endl;
    
    cout<<isSorted({1,1,1,1})<<endl;
    cout<<isSorted({1,1,2,4})<<endl;
    cout<<isSorted({5,4,4,2})<<endl;
    
    cout<<isSorted({1,1,1,4,1,1})<<endl;
    
}
