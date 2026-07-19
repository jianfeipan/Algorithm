/*
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.

 

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2
Example 2:

Input: nums = [3,1,3,4,2]
Output: 3
*/
class Solution {
public:

    // BF: use a data struture: unodered_set
    // time: O(N)
    // space: O(N)
    int findDuplicate_set(vector<int>& nums) 
    {
        unordered_set<int> unique;
        for(auto num : nums)
        {
            if(unique.contains(num)) return num;
            unique.insert(num);
        }

        return -1;
    }

    // nums containing  n+1 integer, [1...n]
    int findDuplicate_bitmap(vector<int>& nums)
    {   
        vector<bool> presented(nums.size(), false);
        for(auto num : nums)
        {
            if(presented[num-1]) return num;
            else presented[num-1] = true;
        }
        return -1;
    }
    // space O(1)?
    // sorting, then one pass, but time O(NlogN)
    //
    // negative marking!!
    // use the -1 as the flag 
    // the [1...n] numers can be used as index to nums of this vector
    // if we got one number already negative, it's the duplicated one
    int findDuplicate_negative_marked(vector<int>& nums)
    {   
        for(int i = 0; i<nums.size(); ++i)
        {
            int current = nums[i];
            if(current<0) current*=-1;
            if(nums[current] < 0) return current;
            nums[current]*=-1;
        }
        
        return -1;
    }

    // linked list!
    // same idea: [1...n] these numbers can be index in this n+1 vector
    // it's a linked list, and if there is duplicaiton, there is a circle
    // to meet the circle, we can use the trick of fast slow pointer
    //
    int findDuplicate(vector<int>& nums)
    {   
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) {
                break;
            }
        }
        // index: 0 1 2 3 4
        // nums:  2 1 3 2 2
        // 1      sf
        // 2          s f 
        // 3            sf --> meet
        // but the meet point is not neccesarly the duplicated number
        // look at this cyrcle: 
        // index: 0 1 2 3 4 5
        // nums:  1 2 3 4 5 2
        // becasue 1 is not in the circle, or it could be something else before going cycle, 
        // the fast & slow is doing: fast eventrually will do one more rand in the circle, but 
        // they doesn't tell you where we start the circle, which is the number duplicated
        // if we look at how many nodes they go over:
        // beforeDup + meetPosIncycle                = SlowDistance = t*1
        // beforeDup + meetPosIncycle + n*nodesInCycle = FastDistance = t*2

        // so we have beforeDup = n*nodesInCycle - meetPosIncycle
        // so when this time we put another pointer slow0 = 0 , and start move by one, 
        // and same time, slow is already at meetPosIncycle, then will do n*nodesInCycle - meetPosIncycle
        // then slow0 and slow will meet at the duplicate point! 

/*
Misunderstanding Floyd's Cycle Detection Entry Point
In the fast and slow pointer approach, the meeting point of the two pointers is not the duplicate number. After they meet, you must start a new pointer from index 0 and move both pointers one step at a time until they meet again. This second meeting point is the cycle entry, which corresponds to the duplicate value.*/
        int slow2 = 0;
        while (true) {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2) {
                return slow;
            }
        }
    
    
    
    }



};
