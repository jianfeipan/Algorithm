/*
You are given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.

You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

Example 1:

Input: nums = [-2,-1,0]

Output: 1
Example 2:

Input: nums = [1,2,4]

Output: 3

if has negative or 0, move them to left: O(n)

if positive, [num-negativeNumsCount]  should be it's place
inplace hash!



*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        const int n = nums.size();
        int offset = -1;
        for(int i=0; i<n; ++i){//O(n)
            if(nums[i]<=0){
                ++offset;
                swap(nums[offset], nums[i]);
            }
        }
        //       n-2=1    2  3  4
        //   0  1 2  3    4  5  6
        // [-2,-1,0, 5  , 2, 1  3]
        // offset index=2
        // for any number, num should be position num+2
        // 5 should be position 5+2 = 7 -> out skip
        // 2 should be 2+2 = 4, which is good
        // 1 should be 1+2 = 3  swap 5 and 1, current is 5-> skip
        // 3 should be 3+2 = 5 -> swap with 5 current becomes 5->skip
        // ...
        for(int i = offset+1; i<nums.size(); ++i){
            int current = nums[i];
            int currentToIndex = current+offset;
            while( currentToIndex != i  
                && nums[i]!=nums[currentToIndex] 
                && currentToIndex<nums.size()){

                swap(nums[i], nums[currentToIndex]);
                current = nums[i];
                currentToIndex = current+offset;
            }
        }
        // after swap: 
        //       n-2=1    2  3  4
        //   0  1 2  3    4  5  6
        // [-2,-1,0, 1  , 2, 3  5]
        //                      ^ this 5 is always the index missing and the number missing is index -2
        
        for(auto& num : nums) cout<<num<<", ";
        cout<<endl;
        
        int missing = 1;
        for(int i = offset+1; i<nums.size(); ++i){
            if(nums[i] != missing)  break;
            else  ++missing;
        }

        return missing;


    }   
};
