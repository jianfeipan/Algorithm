class Solution {
    /*
    Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.

 

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted.
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000


are they sorted ? 
if yes we can use two pointer S:O(1);


    */
    
    
    
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_set<int> uniqueNums;
        for(auto num : nums1) uniqueNums.insert(num);
        
        vector<int> intersections;
        for(auto num : nums2)
            if(uniqueNums.count(num)) 
            {
                intersections.push_back(num);
                uniqueNums.erase(num);//if use map count, we can remove this 
            }
        
        return intersections;
    }
};
