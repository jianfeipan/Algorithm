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
 */

/*
You are given the root of a binary tree with n nodes where each node in the tree has node.val coins. There are n coins in total throughout the whole tree.

In one move, we may choose two adjacent nodes and move one coin from one node to another. A move may be from parent to child, or from child to parent.

Return the minimum number of moves required to make every node have exactly one coin.

*/
class Solution {
public:
    int distributeCoins(TreeNode* root) 
    {
        int need;
        return distributeCoins(root, need);
    }
    
private:
    int distributeCoins(TreeNode* root, int & need) 
    {
        if(!root) return 0;
        
        int leftNeed = 0;
        auto leftSteps = distributeCoins(root->left, leftNeed);
        
        int rightNeed = 0;
        auto rightSteps = distributeCoins(root->right, rightNeed);
        
        const int rest = root->val - leftNeed - rightNeed;
        need = 1 - rest;//I need from parent to have 1
        return abs(need) +rightSteps+leftSteps;
    }
};
