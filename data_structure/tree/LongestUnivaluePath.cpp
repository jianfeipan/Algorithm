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
 Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.

The length of the path between two nodes is represented by the number of edges between them.
 */
class Solution {
    
private:
    int longestPathOfValue(TreeNode * root, int val)//only from root to left or right to have the longest with val
    {
        if(root)
        {
            if(root->val == val)
            {
                return max(
                            longestPathOfValue(root->left, val),
                            longestPathOfValue(root->right, val)
                          ) + 1 ;
            }
        }
        return 0;
    }
    
    int longestUnivaluePathOfRootVal(TreeNode* root) {
        if(root)
        {
            return longestPathOfValue(root->left, root->val) + longestPathOfValue(root->right, root->val);//root links left and right
        }
        return 0;
    }
    
    void DFS(TreeNode* root)
    {
        if(root)
        {
            maxLenth = max(maxLenth, longestUnivaluePathOfRootVal(root));

            DFS(root->left);
            DFS(root->right);
        }
        
    }
    
    int maxLenth;
    
public:
    int longestUnivaluePath(TreeNode* root) {
        maxLenth = 0;
        
        DFS(root);
        
        return maxLenth;
    }
};
