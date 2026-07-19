/*
Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
*/


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
class Solution {
public:
    //typical recusive solution : from biggest number to smallest and use a sum to note current sum
    //use post  order traversal to get from biggest to smallest
    TreeNode* bstToGst(TreeNode* root) {
        int currentSum = 0;
        postOrderBstToGst(root, currentSum);
        return root;
    }
    
private:
    void postOrderBstToGst(TreeNode * root, int & currentSum)
    {
        if(root)
        {
            postOrderBstToGst(root->right, currentSum);
            
            currentSum+=root->val;
            root->val=currentSum;

            postOrderBstToGst(root->left, currentSum);
        }
    }
};
