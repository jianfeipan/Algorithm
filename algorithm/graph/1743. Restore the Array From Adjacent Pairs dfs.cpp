
/*
1743. Restore the Array From Adjacent Pairs
Medium
1.9K
68
Companies
There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.

You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.

It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.

Return the original array nums. If there are multiple solutions, return any of them.

 

Example 1:

Input: adjacentPairs = [[2,1],[3,4],[3,2]]
Output: [1,2,3,4]
Explanation: This array has all its adjacent pairs in adjacentPairs.
Notice that adjacentPairs[i] may not be in left-to-right order.
Example 2:

Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
Output: [-2,4,1,-3]
Explanation: There can be negative numbers.
Another solution is [-3,1,4,-2], which would also be accepted.
Example 3:

Input: adjacentPairs = [[100000,-100000]]
Output: [100000,-100000]
 

Constraints:

nums.length == n
adjacentPairs.length == n - 1
adjacentPairs[i].length == 2
2 <= n <= 105
-105 <= nums[i], ui, vi <= 105
There exists some nums that has adjacentPairs as its pairs.
Accepted
102.7K
Submissions
136.6K
Acceptance Rate
75.2%
*/
class Solution {
    /*
    fact:
        pairs in input is not ordered
        only one order allowed (once we decide the first pair's order, the rest is definded)
    idea:
        we need a structure to let us find easily the adjacent value for a given number->map 4->-2 ,-2->4
        fins out which one is the head (who has only one adj)

    */
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> adjs;adjs.reserve(adjacentPairs.size()*2);

        for(auto adjacentPair : adjacentPairs){
            adjs[adjacentPair[0]].push_back(adjacentPair[1]);
            adjs[adjacentPair[1]].push_back(adjacentPair[0]);
        }

        unordered_set<int> did;
        vector<int> ordered;
        //find the start point : only one adj
        for(const auto & adj : adjs){
            if(adj.second.size() == 1){
                ordered.push_back(adj.first);
                did.insert(ordered.back());
                break;
            }
        }

        if(ordered.empty()) return ordered;

        auto it = adjs.find(ordered.back());


        while(it!=adjs.end() && did.size() <= adjacentPairs.size()){

            for(auto next : it->second){
                auto find = did.find(next);
                if(find == did.end()){
                    ordered.push_back(next);
                    did.insert(ordered.back());
                    it = adjs.find(ordered.back());
                    break;
                }
            }
        }

        /*

        improvements: 
        the condition did is not cheap, here we need only to exclude prev from next's adjs, and we only have two adj 



         while (ans.size() < adjacentPairs.size() + 1) {
            const int tail = ans.back();
            const int prev = ans[ans.size() - 2];
            const vector<int>& adjs = numToAdjs[tail];
            if (adjs[0] == prev)
                ans.push_back(adjs[1]);
            else
                ans.push_back(adjs[0]);
            }
        
        
        
        */

        return  ordered;
    }
};
