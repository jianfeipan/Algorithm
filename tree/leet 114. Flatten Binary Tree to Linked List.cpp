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
    void flatten(TreeNode* root) {
        if(root)
        {
            TreeNode* left = root->left;
            TreeNode* right= root->right;

            flatten(left);
            flatten(right);
            
            if(left) 
            {
                TreeNode * leftTail = getTail(left);
                if(leftTail) leftTail->right = right;
                
                root->right = left;
                root->left = nullptr;
            }
        }
    }
    
private:
    TreeNode * getTail(TreeNode * root)
    {
        if(!root) return nullptr;
        if(root->right == nullptr) return root;
        else return getTail(root->right);
    }
    
};
