#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*

given a sorted array, had to find the first occurrence of given number
*/

int search(const vector<int> & nums, int target, size_t from, size_t to)
{
    if(from == to) return target == nums[from] ? from : -1;
    
    size_t middle = (from+to)>>1;
    if(nums[middle]<target)
    {
        return search(nums, target, middle+1, to);
    }
    else if(nums[middle] > target)
    {
        return search(nums, target, from, middle-1);
        
    }
    else 
    {
        auto onleft =  search(nums, target, from, middle-1);
        if(onleft == -1) return middle;
        else return onleft;
    }
    return -1;
}

int findFirstOccurence(const vector<int> & nums, int target)
{
   return search(nums, target, 0, nums.size()-1);
}
  
int main(int argc, char *argv[])
{
     auto pos = findFirstOccurence({1,2,2,2,3,4,5,6,7}, 2);
     
    cout<<pos<<endl;
    
    return 0;
}
