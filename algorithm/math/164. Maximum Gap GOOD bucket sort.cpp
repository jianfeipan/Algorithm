/*
164. Maximum Gap
Medium

Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.

You must write an algorithm that runs in linear time and uses linear extra space.

 

Example 1:

Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109

*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        /*
        fact:
            linear time: cannot sort (quick sort O(nlogn) )

        idea:
            -1.2..4....8-> we need to find maxgap in a linear time without sorting: if we put buckets with proper size: 4 number ,4 bucket for example
            |1.2|.4|..|.8|-> the max will be the min(bucket i+1) - max(bucket i)
            - how to choose how many bucket?: depends on the bucket size.
            --> how to choose bucket size which make sure the max gap is not inside a bucket?: bucket is the average distance!
              

        */

        if(nums.size()<=1) return 0;

        if(nums.size() == 2) return std::abs(nums[0] - nums[1]);

        
        int min_val = INT_MAX;
        int max_val = INT_MIN;

        for(int num:nums){
            min_val = std::min(min_val, num);
            max_val = std::max(max_val, num);
        } 

        const int size = (max_val - min_val)/(nums.size()-1);
        int bucket_size = std::max(1, size);

        int bucket_count = (max_val - min_val) / bucket_size + 1;

        std::vector<std::pair<int, int>> buckets(bucket_count, {-1, -1});
        for(int num : nums){
            int bucket_index = (num-min_val) / bucket_size;
            
            if(buckets[bucket_index].first == -1){
                buckets[bucket_index].first = buckets[bucket_index].second = num;
            }else{
                buckets[bucket_index].first = std::min(num, buckets[bucket_index].first);
                buckets[bucket_index].second = std::max(num, buckets[bucket_index].second);
            }

        }


        int max_gap = 0;
        int prev_max = min_val;
        for (const auto & bucket : buckets){
            if(bucket.first!=-1){
                max_gap = std::max(max_gap, bucket.first - prev_max);
                prev_max = bucket.second;
            }
        }

        return max_gap;

    }
};
