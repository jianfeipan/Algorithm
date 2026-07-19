class Solution {
public:
    Solution(vector<int>& nums) 
    {
        _nums = nums;
    }
    
    vector<int> reset() 
    {
        return _nums;
    }
    
    vector<int> shuffle() 
    {
        vector<int> shuffled(_nums);
        const size_t size = shuffled.size();
        for(size_t i = 0; i<shuffled.size(); ++i)
        {
            size_t swapWith = rand()%(size - i)+i;//Dont forget the +i to shift your index
            
            if(i!=swapWith)
            {
                auto temp = shuffled[i];
                shuffled[i] = shuffled[swapWith];
                shuffled[swapWith] = temp;
            }
        }
        
        return shuffled;
    }
private:
    vector<int> _nums;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
