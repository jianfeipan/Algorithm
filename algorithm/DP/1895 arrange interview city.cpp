class Solution {
public:
    /**
     * @param cost: The cost of each interviewer
     * @return: The total cost of all the interviewers.
     */
    int TotalCost(vector<vector<int>> &cost) {
        /* greedy : first let all interviewes to be in city A
                    then take the best fit for B : where Ai - Bi is the biggest 
        */
        
        int minTotalCost = 0;
        vector<int> saveByGoingToB(cost.size(), 0);
        for(int i = 0; i<cost.size(); ++i)
        {
            saveByGoingToB[i] = cost[i][0] - cost[i][1];
        }

        std::sort(saveByGoingToB.begin(), saveByGoingToB.end());

        int costAllA = 0;
        for(const auto & c :cost)
        {
            costAllA+=c[0];
        }

        int bestSave = 0;
        for(int i=cost.size()-1; i>=cost.size()/2; i--)
        {
            bestSave+=saveByGoingToB[i];
        }

        return costAllA - bestSave;
    }
};
