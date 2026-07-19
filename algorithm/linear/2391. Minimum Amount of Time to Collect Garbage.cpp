/*
You are given a 0-indexed array of strings garbage where garbage[i] represents the assortment of garbage at the ith house. garbage[i] consists only of the characters 'M', 'P' and 'G' representing one unit of metal, paper and glass garbage respectively. Picking up one unit of any type of garbage takes 1 minute.

You are also given a 0-indexed integer array travel where travel[i] is the number of minutes needed to go from house i to house i + 1.

There are three garbage trucks in the city, each responsible for picking up one type of garbage. Each garbage truck starts at house 0 and must visit each house in order; however, they do not need to visit every house.

Only one garbage truck may be used at any given moment. While one truck is driving or picking up garbage, the other two trucks cannot do anything.

Return the minimum number of minutes needed to pick up all the garbage.

 

Example 1:

Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
Output: 21
Explanation:
The paper garbage truck:
1. Travels from house 0 to house 1
2. Collects the paper garbage at house 1
3. Travels from house 1 to house 2
4. Collects the paper garbage at house 2
Altogether, it takes 8 minutes to pick up all the paper garbage.
The glass garbage truck:
1. Collects the glass garbage at house 0
2. Travels from house 0 to house 1
3. Travels from house 1 to house 2
4. Collects the glass garbage at house 2
5. Travels from house 2 to house 3
6. Collects the glass garbage at house 3
Altogether, it takes 13 minutes to pick up all the glass garbage.
Since there is no metal garbage, we do not need to consider the metal garbage truck.
Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the garbage.

*/

class Solution {
/*
fact: 
    1 cannot skip any house, the traval cost depends where the truc stops (where we have last M,G or P)
    2 cannot skip any trash, all M, G, P will be collected.
    3 no multi-task: every move and every collection taks one --> make it so easy


idea: 
    go over the houses, all garbages is a fix cost for collection
    find where is the last G, P, M, compute the traval cost
*/


public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int lastM = -1;
        int lastG = -1;
        int lastP = -1;

        int cost = 0;
        for(int i = 0; i< garbage.size(); ++i)
        {
            cost+=garbage[i].size();
            for(char c : garbage[i])
            {
                if(c == 'M') lastM = i;
                else if(c == 'G') lastG = i;
                else if(c == 'P') lastP = i;
                //else throw new Exception("unknowGarbage");
            }
        }
        //accumulate traval cost
        int sum=0;
        for(int i = 0; i<travel.size(); ++i)
        {
            //to i+1
            sum+=travel[i];
            if(lastM == i+1) cost+=sum;
            if(lastG == i+1) cost+=sum;
            if(lastP == i+1) cost+=sum;
        }

        return cost;


    }
};
