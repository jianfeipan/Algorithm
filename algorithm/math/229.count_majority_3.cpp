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
            

            // count
            if(num == major1) ++count1;
            else if(num == major2) ++count2;
            else if(count1 == 0) {major1 = num; count1=1;}
            else if(count2 == 0) {major2 = num; count2=1;}
            else{
                --count1;
                --count2;
                /*
                当我们同时减少两个计数器时，本质上是丢弃了三个互不相同的数：候选人 A 的一个实例。候选人 B 的一个实例。当前遇到的第三个不同的数。因为我们每次丢弃的是 3 个不同的数，这种“三方抵消”在长度为 $n$ 的数组中最多只能发生 $n/3$ 次。如果一个元素的出现次数真的超过了 $n/3$，它在经历了所有的抵消之后，一定会有剩余。虽然它的最终计数不一定是它的实际出现次数，但它一定会留在 major1 或 major2 中。*/
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
