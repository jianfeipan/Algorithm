class Solution {

    /*
    
You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:

The 2D array should contain only the elements of the array nums.
Each row in the 2D array contains distinct integers.
The number of rows in the 2D array should be minimal.
Return the resulting array. If there are multiple answers, return any of them.

Note that the 2D array can have a different number of elements on each row.

Example 1:

Input: nums = [1,3,4,1,2,3,1]
Output: [[1,3,4,2],[1,3],[1]]
Explanation: We can create a 2D array that contains the following rows:
- 1,3,4,2
- 1,3
- 1
All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
It can be shown that we cannot have less than 3 rows in a valid array.
    


Fact:
    1 number of buckets depends on most duplicated element 

idea
    1 sort, then same elenmnt sgo to different buckets, if not enough, create new buckets.

    */
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        if(nums.empty()) return {};

        std::sort(nums.begin(), nums.end());
         int current = nums[0];

        vector<vector<int>> buckets;
        buckets.emplace_back(vector<int>{current});
        int currentBucketIndex = 0;
       
        for(int i = 1; i<nums.size(); ++i)
        {
            if(nums[i] == current) //next bucket
            {
                ++currentBucketIndex;
                if(currentBucketIndex == buckets.size())//need a new bucket
                {
                    buckets.push_back({});
                }

                buckets[currentBucketIndex].push_back(nums[i]);
            }
            else// different value, back to bucket 0
            {
                currentBucketIndex = 0;
                buckets[currentBucketIndex].push_back(nums[i]);

                current = nums[i]; //Update current
            }


        }

        return buckets;
    }
};
