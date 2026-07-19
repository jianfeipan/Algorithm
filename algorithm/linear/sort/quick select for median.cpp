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

Break a long list into 2 smaller lists, 1st smaller list has all elements that are smaller than the elements in 2nd list.

list same length
same thing to "find median"

*/

int median(vector<int> nums)
{
    //sort, take the middle one O(NlogN)
    
    //minheap N/2 pop : O(NlogN)
    
    //quick select O(N) --> we only take a half every level
    
    int left = 0;
    int right = nums.size()-1;
    const int target = nums.size()>>1;

    
    while(left<right)
    {
        int smallerZone = left;
        int pivot = nums[right];
        
        int current = left;
        while(current<right)
        {
            if(nums[current] < pivot)
            {
                auto temp = nums[smallerZone];
                nums[smallerZone] = nums[current];
                nums[current] = temp;
                ++smallerZone;
            }
            ++current;
        }
        
        //swapPivot
        auto temp = nums[smallerZone];
        nums[smallerZone] = nums[current];
        nums[current] = temp;
        
        if(smallerZone == target) return nums[smallerZone];
        else if(smallerZone > target)
        {
            right = smallerZone-1;
        }
        else
        {
            left = smallerZone+1;
        }
    }    
    return left;
}


int main()
{
    cout<<median({7,8,9,1,5,10,2,4,3,6,11})<<endl;
}
