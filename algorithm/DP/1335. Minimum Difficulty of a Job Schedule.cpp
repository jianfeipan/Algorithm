class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) 
    {
        vector<vector<int>> minDiffs(jobDifficulty.size(), vector<int>(d+1, -2));
        
        return minDifficulty(jobDifficulty, 0, d, minDiffs);
    }
       
    
    int minDifficulty(const vector<int>& jobDifficulty, int from, int d, vector<vector<int>>& minDiffs) 
    {
        if(jobDifficulty.size() - from < d) return -1;
        
        auto & cache = minDiffs[from][d];
        if(cache != -2) return cache;
        
        if(d == 1)
        {
            int localMaxDiff = INT_MIN;
            for(size_t i = from; i<jobDifficulty.size(); ++i) localMaxDiff = max(localMaxDiff, jobDifficulty[i]);
            
            cache = localMaxDiff == INT_MIN? -1 : localMaxDiff;
            return cache;
        }
        
        if(jobDifficulty.size() - from == d) 
        {
            int sum = 0;
            for(size_t i = from; i<jobDifficulty.size(); ++i) sum+=jobDifficulty[i];
            cache = sum;
            return sum;
        }
        
        int minDiff = INT_MAX;
        
        int maxDiffOnCurrentDay = INT_MIN;
        for(size_t i = from; i<=jobDifficulty.size()-d; ++i)
        {
            maxDiffOnCurrentDay = max(maxDiffOnCurrentDay, jobDifficulty[i]);
            const int nextdiff = minDifficulty(jobDifficulty, i+1, d-1, minDiffs);
            if(nextdiff!=-1)
                minDiff = min(minDiff, maxDiffOnCurrentDay+nextdiff);
        }
        
        cache = minDiff==INT_MAX ? -1 : minDiff;
        return cache; 
    }
    
};
