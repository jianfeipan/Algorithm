class Solution {
public:
    int trap(vector<int>& height) 
    {
        return trap_with_memory_maxLeft_maxRight(height);
    }
    
    int trap_with_memory_maxLeft_maxRight(vector<int>& height) 
    {//Idea2 :  the problem of the brute force is that we counted manytimes the max left and right then most of them are the same : 
     //so we use a cache to not maxLefts and maxRights
        
        vector<int> maxLefts(height.size(), 0);
        vector<int> maxRights(height.size(), 0);
        
        {
            int currentMax = 0;
            for(size_t i=0; i<height.size(); ++i)
            {
                maxLefts[i] = currentMax;
                currentMax = max(height[i], currentMax);
            }
        }
        {
            int currentMax = 0;
            for(int i=height.size()-1; i>=0; --i)
            {
                maxRights[i] = currentMax;
                currentMax = max(height[i], currentMax);
            }
        }
        
        int totalTrap = 0;
        for(size_t i = 0; i < height.size(); ++i)
        {
            totalTrap += max( min(maxLefts[i], maxRights[i]) - height[i], 0);
        }
        return totalTrap;
        
    }

    int trap_brute_force(vector<int>& height) 
    {//Idea1 : for every position, find the left max and right max, and the trap for this position will be min(leftMax, rightMax) - hight[i] 
        
        int totalTrap = 0;
        
        for(size_t i = 0; i< height.size(); ++i)
        {
            int leftMax = findLeftMax(height, i);
            int rightMax = findRightMax(height, i);
            
            totalTrap += max( min(leftMax, rightMax) - height[i], 0);
        }
        
        return totalTrap;
    }
    
private:
    int findLeftMax(const vector<int>& height, int current)
    {
        int leftMax = 0;
        for(int i = current-1; i>=0; --i )
        {
            leftMax = max(leftMax, height[i]);
        }
        return leftMax;
        
    }
    
    int findRightMax(const vector<int>& height, int current)
    {
        int rightMax = 0;
        for(int i = current+1; i<height.size(); ++i )
        {
            rightMax = max(rightMax, height[i]);
        }
        return rightMax;
    }
};
