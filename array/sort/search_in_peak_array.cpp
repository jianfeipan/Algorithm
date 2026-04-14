/*
(This problem is an interactive problem.)

An array arr is called a mountain array if and only if:

arr.length >= 3
There exists some index i with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
You are given a mountain array mountainArr and an integer target, return the minimum index such that mountainArr.get(index) == target. If such an index does not exist, return -1.

You cannot access the mountain array directly. You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
You can only make at most 100 calls to the function get(). Submissions making more than 100 calls will be judged as Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.

Example 1:

Input: mountainArr = [2,4,5,2,1], target = 2

Output: 0
Example 2:

Input: mountainArr = [1,2,3,4,2,1], target = 6

Output: -1
*/

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        const auto n = mountainArr.length();
        int l=-1;
        int r=n;
        // find peak: IS_BLUE = m<m+1
        /* -1  0 1 2 3  4
              [0,5,3,1]

        */

        while(l+1!=r){
            int m = l+(r-l)/2;
            auto mid = mountainArr.get(m);
            auto next = mountainArr.get(m+1);
            if(mountainArr.get(m) < mountainArr.get(m+1)) l=m;
            else r=m;
        }
        int peak = r;
        //search on left: search element
        l = 0;
        r = peak;
        while(l<=r){
            int m = l+(r-l)/2;
            auto mid = mountainArr.get(m);
            if(mid == target) return m;
            if(mid < target) l=m+1;
            else r=m-1;
        }

        //search on right
        l = peak;
        r = n-1;
        while(l<=r){
            int m = l+(r-l)/2;
            auto mid = mountainArr.get(m);
            if(mid == target) return m;
            if(mid > target) l=m+1;
            else r=m-1;
        }

        return -1;

    }
};
