class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        //idea: put everyone to A first, then see move who will save the most, then we move another....util we have a half
        //half is k person, so we need the k top diff --> maxHeap
        
        int costAllCityA = 0;
        for(const auto & cost : costs) costAllCityA+=cost[0];
        
        priority_queue<int> changeToBCouldSave;
        for(const auto & cost : costs) changeToBCouldSave.push(cost[0] - cost[1]);
        
        int maxSaveMoveToB = 0;
        for(int i = 0; i<costs.size()/2; ++i)
        {
            maxSaveMoveToB += changeToBCouldSave.top(),changeToBCouldSave.pop();
        }
        return costAllCityA - maxSaveMoveToB;
    }
};
