
/*
90. Subsets II
Medium
9.3K
273
Companies
Given an integer array nums that may contain duplicates, return all possible 
subsets
 (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10

*/
class Solution {

    /*
    fact: 
        1 start from empty
        2 no duplication
        3 no order 

    idea: 
        1 as a humman, start from 0 element, 1 element ....
            1.1 how to avoid duplication? 
                --> 1.1.1 process generates all possibilitie and remove duplications when output the result
                           []
                            |         \
                        1: []                   [1]
                            | \                   |   \
                        2: []  [2]               [1]          [1,2]
                            |\   |\               |\            |\  
                        2: [][2] [2][2,2]      [1]  [1,2]      [1,2] [1,2,2]

                dedupolication: set<vector<int>>

                --> 1.1.2 find a way to avoid duplication in the process : transform input to a count map
                        [1 2 2]-> 
                            0 element:  []
                            1 element:  [], 1: [1], 2: [2] 2:-[2]-duplicated
                            2 element:  [], [1], [2]  [1, 2], [2,2] []
                        
    
    */

private:
    vector<vector<int>> subsetsWithDup_iterative(vector<int>& nums) {

        std::sort(nums.begin(), nums.end());
        
        set<vector<int>> subSets{{}};
        for(int num: nums ){
            set<vector<int>> nextLevel;
            for(  auto subSet: subSets){
                subSet.push_back(num);
                nextLevel.insert(subSet);
            }
            subSets.insert(
                std::make_move_iterator(nextLevel.begin()), 
                std::make_move_iterator(nextLevel.end()));

        }

        return vector<vector<int>>(
            std::make_move_iterator(subSets.begin()), 
            std::make_move_iterator(subSets.end()));
    }

    void addElement(const vector<int>& nums, int currentIndex, vector<int>& currentSubset, vector<vector<int>>& subSets){
        subSets.push_back(currentSubset);

        if(currentIndex>=nums.size()) return;

        for (int i = currentIndex; i < nums.size(); i++)
        {
            int currentNum = nums[i];
            if (i > currentIndex)
            {
                int prevNum = nums[i - 1];
                if (currentNum == prevNum)
                {
                    continue;//skip repeated 
                }
            }
            currentSubset.push_back(currentNum);
            addElement(nums, i+1, currentSubset,subSets);
            currentSubset.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup_recursive(vector<int>& nums) {

        std::sort(nums.begin(), nums.end());
        vector<vector<int>> subSets;
        vector<int> currentSubset;
        
        addElement(nums, 0, currentSubset, subSets);

        return subSets;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        return subsetsWithDup_recursive(nums);
    }
};


class Solution_2026
{
/*
permution or subset, always back track is a easier way: 
    from index, use it or not use it, r use which number,
    then dfs to the end then pop back to come to the prev state

for duplication
*/

private:
    void _subsetsWithDup(const vector<int>& nums, vector<vector<int>> & res, int index, vector<int>& current )
    {
        if(index == nums.size()){
            res.push_back(current);
            return;
        }

        // use current number
        current.push_back(nums[index]);
        _subsetsWithDup(nums, res, index+1, current);
        current.pop_back();

        // duplications!!!!!!
        //since duplications, if we don't use this, we need skip all duplications
        auto next = index+1;
        while(nums[next] == nums[index]) ++next;

        // skip current number
        _subsetsWithDup(nums, res, next, current);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> current;
        _subsetsWithDup(nums, res, 0, current);
        return res;
    }
};

