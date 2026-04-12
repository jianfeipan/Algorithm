/*
162. Find Peak Element
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.


nums = [1,2,3,1]

find i<j<k
where n_i < n_j > n_k

imagin the nums is increasing, the first decreasing is a peak!
binary search: 
*/

class Solution {
private:
    int findPeak(const vector<int>& nums, int l, int r){
        if(l==r) return l;
        int m = l+(r-l)/2;

        if(nums[m] < nums[m+1]) return findPeak(nums, m+1, r);
        else return findPeak(nums, l, m);
    }
public:
    int findPeakElement(vector<int>& nums) {
        int l = -1;
        int r = nums.size();
        while(l+1!=r){
            int m = l+(r-l)/2;
            if(m+1<nums.size() && nums[m] < nums[m+1]) l = m;
            else r = m;
        }
        //return findPeak(nums, 0, nums.size()-1); // recursive
        return r;
    }
};
