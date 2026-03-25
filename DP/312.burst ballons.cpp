/*
You are given an array of integers nums of size n. The ith element represents a balloon with an integer value of nums[i]. You must burst all of the balloons.

If you burst the ith balloon, you will receive nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then assume the out of bounds value is 1.

Return the maximum number of coins you can receive by bursting all of the balloons.

Example 1:

Input: nums = [4,2,3,7]

Output: 143

Explanation:
nums = [4,2,3,7] --> [4,3,7] --> [4,7] --> [7] --> []
coins =  4*2*3    +   4*3*7   +  1*4*7  + 1*7*1 = 143

*/
/*
idaes:
    for every ballon [1, n-2], we can choose to shoot, 
    then dfs all the branches, 
    find the max coin
    we can use a cache to memorize all states


*/


class Solution_recursive {
public:
    int maxCoins(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        if(nums.size() == 2) return max(nums[0], nums[1]) + nums[0]*nums[1]; 

        int maxCoin = 0;
        for(int i=0; i<nums.size(); ++i){
            vector<int> current = nums;
            current.erase(current.begin() +i);
            maxCoin=max(maxCoin, 
                    maxCoins(current) 
                    + nums[i] * (i==0 ? 1 : nums[i-1]) * (i+1 == nums.size() ? 1 : nums[i+1])
                );
        }
        return maxCoin;
    }
};

// !!!!!!!the key is still the range: 
// here we need to take another way to think: 
// if the last left ballon is k  in [l,r], so the coin is k*(l-1)*(r+1)
// next dfs will be [l,k-1] + [k+1, r]
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        auto filled = nums;
        filled.insert(filled.begin(), 1);
        filled.push_back(1);

        return dfs(filled, 1, filled.size()-2);
    }

    int dfs(vector<int>& nums, int l, int r) {
        if (l > r) return 0;

        int maxCoin = 0;
        for (int i = l; i <= r; i++) {
            // if i is the last left ballon, then it's left will be l-1 and right will be r+1
            int current = nums[l - 1] * nums[i] * nums[r + 1];
            maxCoin = max(maxCoin, current 
                            + dfs(nums, l, i - 1) 
                            + dfs(nums, i + 1, r));
        }
        return maxCoin;
    }
};
