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

void removeZeros(vector<int> & nums)
{
    auto cleaned = nums.begin();
    for(auto current = nums.begin(); current != nums.end(); ++current)
    {
        if(*current != 0)
        {
            *cleaned = *current;
            ++cleaned;
        }
    }
    nums.erase(cleaned, nums.end());
}


int main()
{
    vector<int> nums({0,1,2,0,0,3,0,4,5,0,0,6,0});
    removeZeros(nums);
    for(auto num : nums) cout<<num<<", ";
    return 0;
}
