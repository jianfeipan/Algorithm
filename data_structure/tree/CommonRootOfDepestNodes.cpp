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
Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.
*/
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        deepestRootWithFullChildren = nullptr;
        maxDepth = -1;
        depthOfSubTreeWithAllDeepestChildren(root, 0);

        return deepestRootWithFullChildren;
    }
    
private:
    //from bool to int : we need not only is or not a full children sub tree, but also the max depth of it's lowest children 
    int depthOfSubTreeWithAllDeepestChildren(TreeNode* root, int depth)
    {
        int depthestInCurrentTree = -1;

        if(root)
        {
                      
            if(!root->left && !root->right)
            {
                if(depth>=maxDepth)
                {
                    maxDepth = depth;
                    deepestRootWithFullChildren = root;
                }
                depthestInCurrentTree = depth;
            }
            else if(root->left && root->right)
            {
                int leftDepthest = depthOfSubTreeWithAllDeepestChildren(root->left, depth+1);
                int rightDepthest = depthOfSubTreeWithAllDeepestChildren(root->right, depth+1);
                
                
                if(leftDepthest == rightDepthest)
                {
                    if(leftDepthest>=maxDepth)
                    {
                        maxDepth = leftDepthest;
                        deepestRootWithFullChildren = root;
                    }
                    
                }
                depthestInCurrentTree = max(leftDepthest, rightDepthest);
                    
            }
            else if(root->left)
            {
                
                depthestInCurrentTree = depthOfSubTreeWithAllDeepestChildren(root->left, depth+1);;
                
            }
            else
            {
                depthestInCurrentTree = depthOfSubTreeWithAllDeepestChildren(root->right, depth+1);;
            }
        }

        return depthestInCurrentTree;

    }
    
    
private:
    TreeNode* deepestRootWithFullChildren;
    int maxDepth;
};
