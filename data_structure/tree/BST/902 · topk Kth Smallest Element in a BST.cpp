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
    // inorder traversal
private:
    void visit(TreeNode* root, int& current, int k, int& res) {
        if(!root) return;

        visit(root->left, current, k, res);
        
        ++current;
        if(current == k) { res = root->val; return; }
       
        visit(root->right, current, k, res);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return -1;
        int current = 0;
        int res;
        visit(root, current, k, res);
        return res;
    }
};

