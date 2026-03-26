
/*


1899. Merge Triplets to Form Target Triplet
You are given a 2D array of integers triplets, where triplets[i] = [ai, bi, ci] represents the ith triplet. You are also given an array of integers target = [x, y, z] which is the triplet we want to obtain.

To obtain target, you may apply the following operation on triplets zero or more times:

Choose two different triplets triplets[i] and triplets[j] and update triplets[j] to become [max(ai, aj), max(bi, bj), max(ci, cj)].
* E.g. if triplets[i] = [1, 3, 1] and triplets[j] = [2, 1, 2], triplets[j] will be updated to [max(1, 2), max(3, 1), max(1, 2)] = [2, 3, 2].

Return true if it is possible to obtain target as an element of triplets, or false otherwise.

Example 1:

Input: triplets = [[1,2,3],[7,1,1]], target = [7,2,3]

Output: true
Explanation:
Choose the first and second triplets, update the second triplet to be [max(1, 7), max(2, 1), max(3, 1)] = [7, 2, 3].

Example 2:

Input: triplets = [[2,5,6],[1,4,4],[5,7,5]], target = [5,4,6]

Output: false
*/

/*
idea:

        apply the following operation on triplets zero or more times:-> since it'a max
    -> it's only apply it or not, multi times has the same effect

  0 [2,5,6],
  1 [1,4,4],
  2 [5,7,5]
    
 target
    [5,4,6]

    go over every element, don't take those invalude (any value > target)
    in the rest, if 1, 2, 3 positions has all target, it's true
    

*/
class Solution {
private:
    bool valid(const vector<int>& candidate, const vector<int>& target){
        for(int i = 0; i<target.size(); ++i){
            if(candidate[i]>target[i]) return false;
        }
        return true;
    }

    void tryToMatch(const vector<int>& candidate, const vector<int>& target, unordered_set<int>& match){
        for(int i = 0; i<target.size(); ++i){
            if(candidate[i] == target[i]) match.insert(i);
        }
    }
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        unordered_set<int> match;
        for(const auto& candidate : triplets){
            if(valid(candidate, target)){
                tryToMatch(candidate, target, match);
            }
        }
        return match.size() == target.size();
    }
};
