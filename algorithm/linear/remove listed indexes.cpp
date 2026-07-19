#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

static void removeIndex_in_place(vector<int> & nums, const vector<size_t> &  sortedIndexesToRemove)
{
    
    size_t nextIndex = 0;
    size_t cleanedIndex = 0;
    
    for(size_t current = 0; current<nums.size(); ++current)
    {
        size_t nextIndexToRemove = sortedIndexesToRemove[nextIndex] ;
        if(current == nextIndexToRemove)
        {
            ++nextIndex;
        }
        else if(current < nextIndexToRemove)
        {
           nums[cleanedIndex] = nums[current];
           cleanedIndex++;
        }
    }
    nums.erase(nums.begin()+cleanedIndex, nums.end());
}

static void removeIndex_in_a_new_vector(vector<int> & nums, const vector<size_t> &  sortedIndexesToRemove)
{
    vector<int> output; output.reserve(nums.size() - sortedIndexesToRemove.size());
    
    size_t nextIndex = 0;
    
    for(size_t index = 0; index<nums.size(); ++index)
    {
        
        if(index == sortedIndexesToRemove[nextIndex])
            ++nextIndex;
        else if(index < sortedIndexesToRemove[nextIndex])
        {
            output.push_back(nums[index]);
        }
    }
    nums = output;
}



int main()
{
    cout<< "inplace : "<<endl;
    vector<int> nums({0,1,2,3,4,5,6,7,8,9});
    removeIndex_in_place(nums, {2,4,6,8});
    for(auto num : nums) cout<<num<<", ";
    
    cout<<endl<< "new : "<<endl;    
    nums = {0,1,2,3,4,5,6,7,8,9};
    removeIndex_in_a_new_vector(nums, {2,4,6,8});
    for(auto num : nums) cout<<num<<", ";
    return 0;
}
