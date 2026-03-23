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

class Solution {
public:
    int subarraySum_BF(vector<int>& nums, int k) {
        /*
            BF: check all subarrays: N+N-1+N-1 .. O(N^2), each subarray sum N : O(N^3)
            i j
            [1,2,3]
            there are negative values! shouldn't stop when sum is > k
        */
        int counter = 0;
        for(int l=0; l<nums.size(); ++l){
            for(int r=l; r<nums.size(); ++r){
                int sum=0;
                for(int i=l; i<=r; ++i) sum+=nums[i];
                if(sum == k) ++counter;
            }
        }
        return counter;
    }
    // using a leftSum to reduce sum loop: O(N^2): any range of sum is leftSum1 - leftSum2
    // [1, 2 , 3] -> [0, 1, 3, 6]
    int subarraySum_leftSum(vector<int>& nums, int k){
        vector<int> leftSum = {0};
        for(int i=0; i<nums.size(); ++i){
            leftSum.push_back(nums[i]+*leftSum.rbegin());
        }

        int counter=0;
        for(int l=0; l<nums.size(); ++l){
            for(int r=l; r<nums.size(); ++r){
                if(leftSum[r+1] - leftSum[l] == k) ++counter;
            }
        }

        return counter;
    }
    

    /*
    following the previous idea with leftSum, 
    basically we are looking for leftSum2 - leftSum1 = k
    
    so when we compute leftSum, we can have a map to memorise leftSum and the frequency of the sum
    then for each leftSum, we look in the current map if leftSum - k is already in the map, so we increment the counter
    
    
    */
    int subarraySum(vector<int>& nums, int k){
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
