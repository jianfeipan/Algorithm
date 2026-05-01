/*
You are given an array of integers nums and an integer k. 
There is a sliding window of size k that starts at the left edge of the array. 
The window slides one position to the right until it reaches the right edge of the array.

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
*/

/*
facts:
    1. fixed window k, 
    2. max int he window
idea:
    1. BF: O(n^2)
    2. maintin a strcuture: when I move the window:
        - add the right side value, know the current max
        - remove the left side value and update the structure
        -> from left right, if have have a decreasing number, the previsous smaller num is no more needed
        becaue my window slide to right
        -> monoton stack: remova all smaller when push
        -> however: we need to drop to left side, we need index -> deque

    3 algo: 
        - build the k len window
        - maintain the monoton deque with numbd
        - when move: 
            if front index is out of window: drop it
            while back numbs < right number: pop_back then push the new one
        - and max on every move, will be the back
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //assert(nums.size() < k);

        // if i have a bigger one, i don't care the smaller ones, 
        // so i will have a deacreasing queue: every time I have a bigger one, i pop the smaller ones
        // --> monoton stack

        // however, we need to move element out of window from the front --> monoton deque
        const auto& n =nums.size();
        using Index =int;
        using Value = int;
        deque<pair<Index, Value>> window;// decreasing ex:  5 4 2 1

        vector<int> res; res.reserve(n-k+1);
        for(int r=0; r<n; ++r){
            auto right = nums[r];
            while(!window.empty() && window.back().second < right) window.pop_back();
            window.emplace_back(r, right);
            // 0  1  2  3=r       
            // 1 [2  1  0] 4  2  6        
            if(r>=k) if(window.front().first <=r-k) window.pop_front();
            if(r>=k-1) res.push_back(window.front().second);
        }    

        return res;

    }
};

