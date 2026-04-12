/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
Input: nums = [3,2,3]
Output: [3]

th result can be one or two
*/
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int major1 = INT_MAX;
        int major2 = INT_MAX;
        int count1 = 0;
        int count2 = 0;
        for(auto num : nums){
            // new major
            if(count1 == 0) major1 = num;
            else if(count2 == 0) major2 = num;

            // count
            if(num == major1) ++count1;
            else if(num == major2) ++count2;
            else{
                --count1;
                --count2;
            }
        }

        count1 = 0;
        count2 = 0;
        // real count
        for(auto num : nums){
            if(num == major1) ++count1;
            else if(num == major2) ++count2;
        }

        vector<int> ans;
        if(count1>nums.size()/3) ans.push_back(major1);
        if(count2>nums.size()/3) ans.push_back(major2);

        return ans;

    }
};
