/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

/*

Description
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?


- can we make change of the BST modifications？ K is a more static value, I mean we can design the tree as a tree with left side always have K element, so every time the kth smallest is the root
when you do remove or insertion, just make sure the insertion and remove make the rotation of the root to keep k element on left.

good: quick access the kth smallest number
bad : tree is not well balanced and impact the efficiety of search

- we can add a count number in the node: to count the index from left, insert and remove will update these count in node.

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
    int kthSmallest(TreeNode* root, int k) 
    {
        return inorderVisit(root, k)->val;    
    }
    
private:
    TreeNode * inorderVisit(TreeNode * root, int &k)
    {
        TreeNode * kth = nullptr;
        if(root)
        {
            kth = inorderVisit(root->left, k);

            if(k>0)
            {
                --k;
                if(k==0) kth = root;
                else kth = inorderVisit(root->right, k);
            }
        }
        return kth;
    }
};
