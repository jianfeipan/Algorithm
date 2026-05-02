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
    //  l->m->right order  = Inorder Traversal : recursion
    // TIme O(n) space O(n)
    int _leftFirst(TreeNode* root, int & count, const int k)
    {
        if(!root) return -1;

        const auto left = _leftFirst(root->left, count, k);
        if(left!=-1) return left;

        ++count; if(count == k) return root->val;
    
        const auto right = _leftFirst(root->right, count, k);
        if(right!=-1) return right;
        
        return -1;//not yet
    }

    int kthSmallest(TreeNode* root, int k) 
    {
        int count = 0;
        return _leftFirst(root, count, k);
    }
};
