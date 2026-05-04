/*
You are given two strings word1 and target, each consisting of lowercase English letters.

You are allowed to perform three operations on word1 an unlimited number of times:

Insert a character at any position
Delete a character at any position
Replace a character at any position
Return the minimum number of operations to make word1 equal target.

Example 1:

Input: word1 = "monkeys", target = "money"

Output: 2
Explanation:
monkeys -> monkey (remove s)
monkey -> money (remove k)

Example 2:

Input: word1 = "neatcdee", target = "neetcode"

Output: 3
Explanation:
neatcdee -> neetcdee (replace a with e)
neetcdee -> neetcde (remove last e)
neetcde -> neetcode (insert o)
*/

/*
idea:
    two pointers compare i ->source j->target
        if(!=) min =
            insert: make a extra i to match j-> j++
            delete: try next i to match j->     i++
            replace: i matches j, let's move both like they are equal: i++, j++
             -> recurvesive to next index
!!! you don't realyy need to make the change on the string, just play with the pointers is ok.

*/

class Solution {
private:
    int dfs(const string& src, 
            const string& target,
            int i, int j, vector<vector<int>>& memory){
        if(j == target.size()) return src.size()-i;
        if(i == src.size()) return target.size()-j;

        auto& cache = memory[i][j];
        if(cache!=-1) return cache;

        if(src[i] == target[j]){
            return cache = dfs(src, target, i+1, j+1, memory);
        }else{
            return cache = min({
                1+dfs(src, target, i, j+1, memory), // insert
                1+dfs(src, target, i+1, j+1, memory), // update
                1+dfs(src, target, i+1, j, memory) // delete
            });
        }
    }

public:
    int minDistance(string word1, string target) {
        vector<vector<int>> memory(word1.size(), vector<int>(target.size(), -1));
        return dfs(word1, target, 0, 0, memory);
    }
};
