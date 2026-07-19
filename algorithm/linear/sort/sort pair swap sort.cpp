#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*
sort all the pairs by the x value (1, 1.0) (2, 1.7) (9, 1.4) (3, 2.6)
*/
void sortPairsWithFirst_quickSort(vector<pair<int, double>> & nums)
{
    sort(nums.begin(), nums.end(), [](const auto & left, const auto & right){
        return left.first<right.first;
    });
}

void sortPairsWithFirst_bucketSort(vector<pair<int, double>> & nums)
{
    vector<vector<double>> buckets(100, vector<double>());
    
    for(const auto & num : nums)
    {
        buckets[num.first].push_back(num.second);
    }
    
    size_t index = 0;
    for(size_t i = 0; i<100; ++i)
    {
        if(!buckets[i].empty())
        {
            for(const auto value : buckets[i])
            {
                nums[index] = {i, value};
            }
            ++index;
        }
    }
}


void sortPairsWithFirst_swap_Sort(vector<pair<int, double>> & nums)
{
    for(size_t i = 0; i<nums.size(); ++i)
    {
        while(nums[i].first>i)
        {
            const int j = nums[i].first;
            auto temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
}

void sortPairsWithFirst(vector<pair<int, double>> & nums)
{
    sortPairsWithFirst_swap_Sort(nums);
}

int main(int argc, char *argv[])
{
    vector<pair<int, double>> nums({
     {3,3.},
     {4,4},   
     {2,2},   
     {5,5},   
     {0, 0},   
     {1, 1},
     {1, 1.1}    
    });
    
    sortPairsWithFirst(nums);

    for(const auto & word : nums) cout<<word.first<<", ";
    cout<<endl;

    return 0;
}
