class Solution {
public:
    
    int minDistance(vector<int>& houses, int k) 
    {
        vector<vector<int>> dpCache(100, vector<int>(100, -1));
        sort(houses.begin(), houses.end());
        return minDistance_DP(houses, k, 0, dpCache);
    }
    
    int minDistance_DP(const vector<int>& houses, int k, int from, vector<vector<int>> & dpCache) 
    {
        if(dpCache[k][from] != -1) return dpCache[k][from];
        
        if(k==1) 
        {
            int cost = 0;
            for(size_t left = from, right = houses.size()-1; left<right; ++left, --right)
            {
                cost += (houses[right] - houses[left]);
            }
            dpCache[k][from] = cost;
            return cost;
        }
        
        int minCost = INT_MAX;
        
        //I have {houses.size() - k} choices for the first mailbox :
        for(size_t i = from; i<=houses.size()-k; ++i)
        {
            int leftSide = 0;
            for(size_t left = from, right =i; left<right; ++left, --right) leftSide += (houses[right] - houses[left]);
            
            const int rightSide = minDistance_DP(houses, k-1, i+1, dpCache);
            
            minCost = min(minCost, leftSide + rightSide);
        }
        dpCache[k][from] = minCost;
        return minCost;
    }
    
};
