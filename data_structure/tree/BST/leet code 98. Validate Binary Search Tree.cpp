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
    // rules: all left nodes are smaller than root, all right nodes are bigger
    // (leftLimit, rightLimit)
    // time O(N) space O(N)
    bool _isValidBST(TreeNode* current, int leftLimit, int rightLimit)
    {
        if(!current) return true;
        if(leftLimit < current->val && current->val < rightLimit)
        {
            return _isValidBST(current->left, leftLimit, current->val) 
                && _isValidBST(current->right, current->val, rightLimit);
        }
        return false;
    }
    
    bool isValidBST(TreeNode* root) {
        return _isValidBST(root, INT_MIN, INT_MAX);
    }
};
