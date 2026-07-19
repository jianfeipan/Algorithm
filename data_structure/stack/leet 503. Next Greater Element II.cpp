class Solution {
public:
    
    vector<int> nextGreaterElements(vector<int>& nums) {
        //Idea: find the max, from the max, go left with a monoton stack
        
        size_t size = nums.size();
        vector<int> nextGreaters(size, 0);
        
        stack<int> right;//monoton stack

        for(int n = size*2-1; n>=0; --n)
        {
            const int i =  n%size;
            
            while(!right.empty() && nums[i] >= right.top()) right.pop();
            
            if(!right.empty())  nextGreaters[i] = right.top();
            else                nextGreaters[i] = -1;
            
            right.push(nums[i]);
        }
        return nextGreaters;
        
        
    }
};
