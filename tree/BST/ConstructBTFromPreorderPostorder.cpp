/*

Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.

If there exist multiple answers, you can return any of them.


[1]
[1]
[1,2,3]
[2,3,1]
[1,2,4,5,3,6,7]
[4,5,2,6,7,3,1]



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
 preorder = [1,2,3,4] -> root left, right
 inorder =  [2,1,3,4] -> left root right
*/
class Solution {
private:
    unordered_map<int, int> pos;
    TreeNode* build_tree_(
        const vector<int>& preorder, 
        int preorder_l, int preorder_r,
        const vector<int>& inorder,
        int inorder_l, int inorder_r) {
        
        if(preorder_l > preorder_r || inorder_l > inorder_r) return nullptr;

        auto root = new TreeNode(preorder[preorder_l]);
        if(preorder_r == preorder_l) return root;

        auto root_pos_inorder = pos[root->val];
        auto left_size =  root_pos_inorder - inorder_l;

        root->left = build_tree_(preorder, preorder_l+1, preorder_l+left_size , inorder, inorder_l , root_pos_inorder-1);
        root->right = build_tree_(preorder, preorder_l+left_size+1, preorder_r, inorder, root_pos_inorder+1 , inorder_r);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pos.clear();
        for(int i=0; i<inorder.size(); ++i) pos[inorder[i]] = i;
        return build_tree_(preorder, 0, preorder.size() -1 , inorder, 0 , inorder.size() - 1);
    }
};
