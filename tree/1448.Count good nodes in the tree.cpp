/*
Within a binary tree, a node x is considered good if the path from the root of the tree to the node x contains no nodes with a value greater than the value of node x

Given the root of a binary tree root, return the number of good nodes within the tree.

Example 1:



Input: root = [2,1,1,3,null,1,5]

Output: 3


Example 2:

Input: root = [1,2,-1,3,4]

Output: 4
Constraints:

1 <= number of nodes in the tree <= 100
-100 <= Node.val <= 100
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

    // left | right > root
    // childe > max; max = max(max, root)
    int _goodNodes(TreeNode* current, int pathMax)
    {
        if(!current) return 0;

        int count = 0;
        if(current->val >= pathMax)
        {
            pathMax=current->val;
            ++count;
        } 
        count+=_goodNodes(current->left, pathMax);
        count+=_goodNodes(current->right, pathMax);
        return count;

    }
    int goodNodes(TreeNode* root) 
    {

        return _goodNodes(root, INT_MIN);
    }
};
