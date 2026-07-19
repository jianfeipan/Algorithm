class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) 
    {
        
        sort(people.begin(), people.end(), [](const auto & left, const auto & right)
             {
                 if(left[0] == right[0]) return left[1] < right[1];
                 else return left[0] > right[0];
             });
        
        list<vector<int>> queue;
        
        for(const auto & p : people)
        {
            auto it = queue.begin();
            advance(it, p[1]);
            queue.insert(it, p);
        }
        
        return vector<vector<int>>(queue.begin(), queue.end());
        
    }
};
