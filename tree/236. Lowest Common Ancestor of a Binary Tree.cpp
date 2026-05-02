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

    // tree is a perfect strucutre for recursion!
    // p and q is on the same branch: left is the common ancestor
    // then we do the same, until p and q are no more ont he same side or the root is one of them
    // time O(logN), space O(logN)
    TreeNode* lowestCommonAncestor_recursion(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!p || !q || !r) return nullptr;
        //the fact is that this is BST, so the compare is easy
        if(p->val < root->val && q->val < root->val)
            return lowestCommonAncestor_recursion(root->left, p, q);
        else if(p->val > root->val && q->val > root->val)
            return lowestCommonAncestor_recursion(root->right, p, q);
        else // different side or equals to root
            return root;
    }

    // in a iterative way
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //the fact is that this is BST, so the compare is easy
        auto current = root;
        while(current)
        {
            if(p->val < current->val && q->val < current->val)
                current = current->left;
            else if(p->val > current->val && q->val > current->val)
                current = current->right;
            else // different side or equals to root
                return current;
        }
        return nullptr;//cannot reach
    }
};
