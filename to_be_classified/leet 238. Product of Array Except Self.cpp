class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefixProduct = vector<int>(nums.size(), 1);
        //prefixProduct[i] = nums[0]*...nums[i-1]
        {//cumulate from left   
            for(int i = 1; i<prefixProduct.size(); ++i)
                prefixProduct[i] = prefixProduct[i-1] * nums[i-1];
        }

        vector<int> suffixProduct = vector<int>(nums.size(), 1);
        //prefixProduct[i] = nums[i+1]*...nums[n-1]
        {//cumulate from right   
            for(int i = suffixProduct.size() - 2; i>=0; --i)
                suffixProduct[i] = suffixProduct[i+1] * nums[i+1];
        }

        vector<int> products(nums.size(), 1);
        for(int i=0; i<products.size(); ++i) products[i]=prefixProduct[i] * suffixProduct[i];
        
        return products;
    }
};
