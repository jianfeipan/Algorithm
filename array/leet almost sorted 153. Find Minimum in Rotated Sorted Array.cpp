class Solution {
public:
    int findMin(vector<int> &nums) {
        if(nums.size()==1) return nums[0];
        // find decreasing

        int l = 0;
        int r = nums.size()-1;
        while(l<r){
            auto m = l+(r-l)/2;
            if(nums[m] > nums[r]) l=m+1; // the min is on the right, because m is smaller than r, so m cannot be the min, so l=m+1
            else r=m; 
        }
        return nums[l];

    }
};
