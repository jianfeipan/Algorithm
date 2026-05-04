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


class Solution_recursive_BF {
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
// if the last left ballon is k  in [l,r], so the coin is k*(l)*(r)


class Solution {
private:
    int max_score_end_with(int l, int r, const vector<int>& score){
        if(l+1 >= r) return 0; // no ballon to shoot
        int max_score = 0;
        for(int i = l+1; i<r; ++i){
            auto current_shoot = score[l]*score[i]*score[r];
            max_score = max(max_score, 
                            current_shoot 
                            + max_score_end_with(l, i, score) 
                            + max_score_end_with(i, r, score));
        }

        return max_score;
    }
public:
    int maxCoins(vector<int>& nums) {
        vector<int> extended(nums.size()+2, 1);
        for(int i=0; i<nums.size(); ++i) extended[i+1] = nums[i];
        // [4,2,3,7]  --> [1, 4,2,3,7, 1]

        return max_score_end_with(0, extended.size()-1, extended);

        
    }
};

