/*

You are given an array of integers nums and an integer k. There is a sliding window of size k that starts at the left edge of the array. The window slides one position to the right until it reaches the right edge of the array.

Return a list that contains the maximum element in the window at each step.

Example 1:

Input: nums = [1,2,1,0,4,2,6], k = 3

Output: [2,2,4,4,6]

Explanation:
Window position            Max
---------------           -----
[1  2  1] 0  4  2  6        2
 1 [2  1  0] 4  2  6        2
 1  2 [1  0  4] 2  6        4
 1  2  1 [0  4  2] 6        4
 1  2  1  0 [4  2  6]       6
Constraints:*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        vector<int> maxInWindow; maxInWindow.reserve(nums.size() - k +1);

        deque<int> biggerIndex; // only take bigger 
        //build window [0,k-1] with monoton queue
        for(int i=0; i<k; ++i){
            while(!biggerIndex.empty() && nums[biggerIndex.back()] < nums[i]) biggerIndex.pop_back(); // keep only bigger value
            biggerIndex.push_back(i);
        }
        maxInWindow.push_back(nums[biggerIndex.front()]);

        //slide window from k
        for(int i=k; i<nums.size(); ++i){
            while(!biggerIndex.empty() && nums[biggerIndex.back()] < nums[i]) 
                biggerIndex.pop_back(); // keep only bigger value
            
            biggerIndex.push_back(i);
            
            if(biggerIndex.front()<=i-k) biggerIndex.pop_front(); // window slide out
            
            maxInWindow.push_back(nums[biggerIndex.front()]);
        }

        return maxInWindow;
    }
};
