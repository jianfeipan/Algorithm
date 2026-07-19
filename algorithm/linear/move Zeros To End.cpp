#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>
#include <sstream>
#include <stack>
/*

https://www.geeksforgeeks.org/cpp-program-to-move-all-zeroes-to-end-of-array/
*/
using namespace std;

void moveZerosToEnd(vector<int> & nums)
{
    size_t noZeroZone = 0;
    for(auto num : nums) {
        if(num){
            nums[noZeroZone] = num;
            ++noZeroZone;
        }
    }
    for(size_t index = noZeroZone; index<nums.size(); ++index) nums[index] = 0;
}

int main()
{
    vector<int> nums({0,0,0,1,0,2,5,3,0,1,4,5,0,2,0,0});
   
    moveZerosToEnd(nums);
   
    for(auto num : nums) cout<<num<<", ";
    cout<<endl;
   
    return 0;
}
