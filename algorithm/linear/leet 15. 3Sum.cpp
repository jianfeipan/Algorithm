class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        const auto& n=nums.size();

        sort(nums.begin(), nums.end());//nlogn

        for(int i=0; i<n-2; ++i){
            const auto target = -1*nums[i];
            int l = i+1;
            int r = n-1;
            while(l<r){
                auto current = nums[l]+nums[r];
                if(current<target) ++l;
                else if(current>target) --r;
                else{
                    res.push_back({nums[i], nums[l], nums[r]});
                    break;
                }
            }
        }
        // O(n^2)
        return res;
    }
};
