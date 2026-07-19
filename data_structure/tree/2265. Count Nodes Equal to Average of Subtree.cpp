/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };

Given the root of a binary tree, return the number of nodes where the value of the node is equal to the average of the values in its subtree.

Note:

The average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
A subtree of root is a tree consisting of root and all of its descendants.
 
Input: root = [4,8,5,0,1,null,6]
Output: 5
Explanation: 
For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4.
For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 / 2 = 5.
For the node with value 0: The average of its subtree is 0 / 1 = 0.
For the node with value 1: The average of its subtree is 1 / 1 = 1.
For the node with value 6: The average of its subtree is 6 / 1 = 6.




 */
class Solution {
/*
fact: 

    

idea:
    DFS + 2  values --> returned : count and sum


*/
private:
    std::pair<int, int> dfs(TreeNode* root, int & res) 
    {

        if(!root) return {0, 0};

        int count = 1;
        int sum = root->val;
        const auto & left_count_sum = dfs(root->left, res);
        if(left_count_sum.first)
        {
            count+=left_count_sum.first;
            sum+=left_count_sum.second;
        }

        const auto & right_count_sum = dfs(root->right, res);
        if(right_count_sum.first)
        {
            count+=right_count_sum.first;
            sum+=right_count_sum.second;
        }

        if(root->val == (sum/count)) ++res;

        
        return {count, sum};
    }

public:
    int averageOfSubtree(TreeNode* root) {


        int averageOfSubtreeCount = 0 ;
        
        dfs(root, averageOfSubtreeCount);


        return averageOfSubtreeCount;

    }
};
