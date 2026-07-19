class Solution {
/*
    pick two numbers n1 + n2 = k -> one operations
    max number of operations
    Constraints:
            1 <= nums.length <= 105
            1 <= nums[i] <= 109
            1 <= k <= 109    
*/
public:
    int maxOperations(vector<int>& nums, int k) 
    {
        return maxOperations_frequece_ordered_map(nums, k);
    }
    
private:
    int maxOperations_frequece_ordered_map(const vector<int>& nums,int k) //O(NlogN) space : O(N)
    {
        /*
        we need a ordered, unique vector of nums, with count : or we can do the sort then two pointer for sum
        */
        int operationsCount = 0;
        map<int, int> diagram;
        for(int num : nums) ++diagram[num];
        
        for(auto[num, count] : diagram)
        {
            if(diagram.count(k - num))
            {
                if(k == num + num) operationsCount += diagram[num]>>1;
                else operationsCount += min(diagram[num], diagram[k-num]);

                diagram[num] = diagram[k-num] = 0;//avoid duplication
            }
        }
        return operationsCount;
    }

    
    
    int maxOperations_brute_force(vector<int> nums, const int k) //O(N^2)
    {
        int count = 0;
        
        for(size_t i = 0; i < nums.size(); ++i)
        {
            if(nums[i]!=-1)
            {
                for(size_t j = i+1; j<nums.size(); ++j)
                {
                    if(nums[j]!=-1 && k == nums[i] + nums[j])
                    {
                        nums[i] = -1;nums[j] = -1;
                        ++count;
                        break;
                    }
                }
            }
        }
        
        return count;   
    }
    
};
