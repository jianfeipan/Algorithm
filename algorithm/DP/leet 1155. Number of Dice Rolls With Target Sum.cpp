class Solution {
    
    /*
        n nums, num [1-k], we need : sum = target
        How many ways?
        
        MODULO 1e9+7
    
    */
public:
    int numRollsToTarget(int n, int k, int target) 
    {
        cache = vector<vector<int>>(n+1, vector<int>(target+1, -1));
        m = 1e9 + 7;
        return numRollsToTarget_recusive(n,k,target);
    }
    
private:
    int numRollsToTarget_recusive(int n, int k, int target) 
    {
        if(target <= 0) return 0;
        
        if(cache[n][target] != -1) return cache[n][target];
        
        if(n == 1) 
        {
            cache[n][target] = 1<=target && target<=k  ? 1 : 0;
            return cache[n][target];
        }
        int counter = 0;
        
        for(int current = 1; current<=k && target > current; ++current)
        {
            counter+= numRollsToTarget_recusive(n-1, k, target - current) % m;
            counter = counter%m;
        }
        cache[n][target] = counter;
        return counter;
    }
public:
    vector<vector<int>> cache;
    int m;
};
