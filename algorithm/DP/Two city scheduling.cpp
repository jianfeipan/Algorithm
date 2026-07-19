/*
A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person to city b is bCosti.

Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.

[[10,20],[30,200],[400,50],[30,20]]
[[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
[[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]


https://en.wikipedia.org/wiki/Assignment_problem
*/

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& cost) {
        //greedy : all to A then see which are the ones move to B will make best save: the ones with biggest A-B
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
