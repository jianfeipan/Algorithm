
/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105


*/
class Solution {

/*
[0,1,0,2,1,0,1,3,2,1,2,1]
every high, water be trapped is the min(leftMax, rightMax)
to find left max: one pass with a vector noted
        right max: one pass
then we sum the min(leftMax, rightMax)
*/
public:
    int trap(vector<int>& height) {
        if(height.size()<=2) return 0;
        vector<int> leftMax=height;
        for(int i=1; i<leftMax.size(); ++i){
            leftMax[i] = max(leftMax[i], leftMax[i-1]);
        }
        vector<int> rightMax=height;
        for(int i=rightMax.size()-2; i>=0; --i){
            rightMax[i] = max(rightMax[i], rightMax[i+1]);
        }

        int sum=0;
        for(int i=1; i<=height.size()-2; ++i){
            auto maxHight = min(leftMax[i], rightMax[i]);
            sum+=max(maxHight - height[i], 0);
        }
        return sum;
    }
};
