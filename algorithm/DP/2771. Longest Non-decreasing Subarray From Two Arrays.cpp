/*

You are given two 0-indexed integer arrays nums1 and nums2 of length n.

Let's define another 0-indexed integer array, nums3, of length n. For each index i in the range [0, n - 1], you can assign either nums1[i] or nums2[i] to nums3[i].

Your task is to maximize the length of the longest non-decreasing subarray in nums3 by choosing its values optimally.

Return an integer representing the length of the longest non-decreasing subarray in nums3.

Note: A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums1 = [2,3,1], nums2 = [1,2,1]
Output: 2
Explanation: One way to construct nums3 is: 
nums3 = [nums1[0], nums2[1], nums2[2]] => [2,2,1]. 
The subarray starting from index 0 and ending at index 1, [2,2], forms a non-decreasing subarray of length 2. 
We can show that 2 is the maximum achievable length.
Example 2:

Input: nums1 = [1,3,2,1], nums2 = [2,2,3,4]
Output: 4
Explanation: One way to construct nums3 is: 
nums3 = [nums1[0], nums2[1], nums2[2], nums2[3]] => [1,2,3,4]. 
The entire array forms a non-decreasing subarray of length 4, making it the maximum achievable length.
Example 3:

Input: nums1 = [1,1], nums2 = [2,2]
Output: 2
Explanation: One way to construct nums3 is: 
nums3 = [nums1[0], nums1[1]] => [1,1]. 
The entire array forms a non-decreasing subarray of length 2, making it the maximum achievable length.


nums1 = [2,3,1], 
nums2 = [1,2,1]

nums3[i] = nums2 or nums1 [i]
nums3   [.....]

longest subarray in nums3

*/

/*
         i
nums1 = [2,3,1], 
nums2 = [1,2,1]

longestFromIndex (currentIndex, prev)
    if(from == N) return 0;
    current > num: return 1+longestFromIndex(currentIndex+1, currentChoice)
    all current < return 0;

*/
class Solution {
private:
    int maxNonDecreasing(const vector<int>& nums1, const vector<int>& nums2, 
                        int from, int prev, vector<vector<int>>& memory){ // prev=0 meas we took nums1 for from-1
        if(from == nums1.size()) return 0;

        auto& cache = memory[from][prev];
        if(cache!=-1) return cache;

        auto prevNum = prev==0 ? nums1[from-1] : nums2[from-1];
        int maxLen = 0;

        if(nums1[from] >= prevNum) maxLen=max(maxLen, 1+maxNonDecreasing(nums1, nums2, from+1, 0, memory));
        if(nums2[from] >= prevNum) maxLen=max(maxLen, 1+maxNonDecreasing(nums1, nums2, from+1, 1, memory));
        return cache = maxLen;
    }
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        const int N = nums1.size();
        if(N<=1) return N;
        int maxLen = 0;

        vector<vector<int>> memory(nums1.size(), vector<int>(2, -1));
       

        for(int i=0; i<N-1;++i){
            maxLen = max(maxLen, 
                    1 + max(
                        maxNonDecreasing(nums1, nums2, i+1, 0, memory),
                        maxNonDecreasing(nums1, nums2, i+1, 1, memory)
                    )
            );
        }
        return maxLen;
    }

     int maxNonDecreasingLength(vector<int>& A, vector<int>& B) {

        //              n-1   n-2 ...
        //  0 nums1      1
        //  1 nums2      1


        /*
        dp1 means the maximum step ending with A[i].
        dp2 means the maximum step ending with B[i].

        Then cosider these 4 transitions:
        t11 for A[i - 1] -> A[i]
        t12 for A[i - 1] -> B[i]
        t21 for B[i - 1] -> A[i]
        t22 for B[i - 1] -> B[i]

        We update
        dp1 = max(t11, t21)
        dp2 = max(t12, t22)
        res = max(res, dp1, dp2)*/

        int res = 1, dp1 = 1, dp2 = 1, n = A.size(), t11, t12, t21, t22;
        for (int i = 1; i < n; ++i) {
            t11 = A[i - 1] <= A[i] ? dp1 + 1 : 1;
            t12 = A[i - 1] <= B[i] ? dp1 + 1 : 1;
            t21 = B[i - 1] <= A[i] ? dp2 + 1 : 1;
            t22 = B[i - 1] <= B[i] ? dp2 + 1 : 1;
            dp1 = max(t11, t21);
            dp2 = max(t12, t22);
            res = max(res, max(dp1, dp2));
        }
        return res;
    }

};
