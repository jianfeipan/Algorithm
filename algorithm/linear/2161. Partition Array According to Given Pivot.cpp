class Solution {

    /*
    You are given a 0-indexed integer array nums and an integer pivot. Rearrange nums such that the following conditions are satisfied:

Every element less than pivot appears before every element greater than pivot.
Every element equal to pivot appears in between the elements less than and greater than pivot.
The relative order of the elements less than pivot and the elements greater than pivot is maintained.
More formally, consider every pi, pj where pi is the new position of the ith element and pj is the new position of the jth element. For elements less than pivot, if i < j and nums[i] < pivot and nums[j] < pivot, then pi < pj. Similarly for elements greater than pivot, if i < j and nums[i] > pivot and nums[j] > pivot, then pi < pj.
Return nums after the rearrangement.

 

Example 1:

Input: nums = [9,12,5,10,14,3,10], pivot = 10
Output: [9,5,3,10,10,12,14]
Explanation: 
The elements 9, 5, and 3 are less than the pivot so they are on the left side of the array.
The elements 12 and 14 are greater than the pivot so they are on the right side of the array.
The relative ordering of the elements less than and greater than pivot is also maintained. [9, 5, 3] and [12, 14] are the respective orderings.



fact:
    1 cannot know the correct index before going tranversing all numbers

idea:
    1 very simple is put 3 vectors (or two vectors and a counter) as buckets, traverse all numbers then combien them again 
    2 another thought is bese on the fact 1: we can do a count, then put the right number to the right place
    
    */
public:
    vector<int> pivotArray_multi_vectors(vector<int>& nums, int pivot) {
        vector<int> smallers;
        int pivotCount = 0;
        vector<int> biggers;

        for(int num : nums)
        {
            if(num == pivot) ++pivotCount;
            else if(num<pivot) smallers.push_back(num);
            else biggers.push_back(num);
        }


        vector<int> res; res.reserve(nums.size());

        for(int num : smallers ) res.push_back(num);

        res.insert(res.end(), pivotCount, pivot);

        for(int num : biggers ) res.push_back(num);

        return res;
    }

    //find the index, then do the put value, save memory anc copy
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int smallerCount = 0;
        int pivotCount = 0;
        int biggerCount = 0;

        for(int num : nums)
        {
            if(num == pivot) ++pivotCount;
            else if(num<pivot) ++smallerCount;
            else ++biggerCount;
        }


        vector<int> res(nums.size());
        int smallerIndex = 0;
        int pivotIndex = smallerCount;
        int biggerIndex = smallerCount+pivotCount;

        for(int num : nums)
        {
            if(num == pivot)
            { 
                res[pivotIndex] = num; 
                ++pivotIndex;
            }
            else if(num<pivot)
            {
                res[smallerIndex] = num; 
                ++smallerIndex;

            } 
            else
            {
                res[biggerIndex] = num; 
                ++biggerIndex;
            } 
        }

        return res;
    }
};
