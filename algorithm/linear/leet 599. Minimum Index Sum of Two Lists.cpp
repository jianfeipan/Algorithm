class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) 
    {
        unordered_map<string, int> indexes2;
        for(size_t i = 0 ; i< list2.size(); ++i) indexes2[list2[i]] = i;

        int minSum = INT_MAX;
        
        vector<string> minNames;
        for(size_t i = 0 ; i< list1.size(); ++i)
        {
            const auto & name = list1[i];
            auto it = indexes2.find(name);
            if(it!= indexes2.end())
            {
                const int sum = i+ it->second;
                if(sum < minSum)
                {
                    minNames.clear();
                    minSum = sum;
                    minNames.push_back(name);
                }
                else if(sum == minSum)
                {
                    minNames.push_back(name);
                }
            }
        }
        return minNames;
    }
};
