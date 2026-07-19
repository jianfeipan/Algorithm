class Solution {
public:
    int minOperations(int n) {
        vector<int> nums(n, 0);

        for(int i = 0; i<n; ++i) nums[i] = 2*i +1;

        int target = (nums[0] + nums[n-1] ) / 2;

        int sum = 0;

        for(int i = 0; i<n/2; ++i)
        {
            sum+= (target - nums[i]);
        }
        return sum;
    }


    //math  return (n%2==0) ? (n/2)*(1ll)*(n/2) :  ((n/2)+1)*(1ll)*(n/2);
};
