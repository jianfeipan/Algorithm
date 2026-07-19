class Solution {
public:
    int countPairs(vector<int>& deliciousness) 
    {
        return countPairs_hash_map_prequece_from_count_left(deliciousness);
    }
    
private:
    int countPairs_hash_map_prequece_from_count_left(const vector<int>& deliciousness) 
    {
        const unsigned int M = 1e9 + 7;
        
        int count = 0;
        unordered_map<int , int> restDishes;

        for(int i = 0;i<deliciousness.size();i++)//count from left, while the rest is on the left
        {
            for(int p = 1;p <= 1<<21;p *= 2)
            {
                if(restDishes.count(p-deliciousness[i]) && restDishes[p-deliciousness[i]])
                    count = (count+restDishes[p-deliciousness[i]])%M;
            }
            restDishes[deliciousness[i]]++;
        }

        return count;
    }
};
