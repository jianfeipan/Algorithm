
/*
You are given a 0-indexed integer array nums of even length consisting of an equal number of positive and negative integers.

You should rearrange the elements of nums such that the modified array follows the given conditions:

Every consecutive pair of integers have opposite signs.
For all integers with the same sign, the order in which they were present in nums is preserved.
The rearranged array begins with a positive integer.
Return the modified array after rearranging the elements to satisfy the aforementioned conditions.

 

Example 1:

Input: nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]
Explanation:
The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4].
The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect because they do not satisfy one or more conditions.  
Example 2:

Input: nums = [-1,1]
Output: [1,-1]
Explanation:
1 is the only positive integer and -1 the only negative integer in nums.
So nums is rearranged to [1,-1].


*/
class Solution {

    /*
    fact:
        1 positive negative alternativly ranged
        2 keep the same order as before
    idea:
        use 2 extra vector, then merge them.
    */
public:
    vector<int> rearrangeArray_extra_vector(vector<int>& nums) {
        vector<int> p;p.reserve(nums.size()/2);
        vector<int> n;n.reserve(nums.size()/2);

        for(const auto & num : nums)
        {
            if(num > 0) p.push_back(num);
            else n.push_back(num);
        }
        int j = 0;
        for(int i = 0; i<n.size(); ++i)
        {
            nums[j] = p[i];++j;
            nums[j] = n[i];++j;

        }
        return nums;
    }

    vector<int> rearrangeArray(vector<int>& nums) {//Inplace 
        int nIndex= 1;
        int pIndex= 0;
        vector<int> res(nums.size(), 0);

        for(const auto & num : nums)
        {
            if(num > 0) 
            {
                res[pIndex] = num;
                pIndex+=2;
            }
            else
            {
                res[nIndex] = num;
                nIndex+=2;
            } 
        }
        
        return res;
    }
};
