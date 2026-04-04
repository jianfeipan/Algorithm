/*
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
*/


    /*
    following the previous idea with leftSum, 
    basically we are looking for leftSum2 - leftSum1 = k
    
    so when we compute leftSum, we can have a map to memorise leftSum and the frequency of the sum
    then for each leftSum, we look in the current map if leftSum - k is already in the map, so we increment the counter
    
    
    */
    int subarraySum_onepass(vector<int>& nums, int k){
        unordered_map<int, int> sumFrequency; // this sum has how many substrings
        sumFrequency[0] = 1; // this is the base: for sum of zero, we have one solution

        int leftSum = 0;
        int count = 0;
        for(const auto& num : nums){
            leftSum += num;

            auto sum2 = leftSum - k;
            if(sumFrequency.count(sum2)){
                count+= sumFrequency[sum2];
            }

            ++sumFrequency[leftSum];
        }

        return count;
    }
};
