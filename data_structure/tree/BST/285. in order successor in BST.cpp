/*
LeetCode 285, Inorder Successor in BST, 
Binary Search Tree (BST) properties and tree traversal.

The Goal
Given a Binary Search Tree and a target node p, 
you need to find the inorder successor of that node.

Inorder Successor: The node with the smallest key greater than p.val.

Inorder Traversal: 
In a BST, an inorder traversal (Left $\rightarrow$ Root $\rightarrow$ Right) 
visits nodes in ascending sorted order.The Two Main ScenariosTo solve this efficiently,
you have to consider where the successor could be hiding based on the structure of the tree.
1. Node p has a Right ChildIf the node has a right subtree, the successor is the leftmost node of that right subtree. 
You simply go right once, then go left as far as possible.
2. Node p has NO Right ChildThis is the trickier part. 
If there is no right child, the successor is one of the ancestors. 
Specifically, it is the lowest ancestor of p such that p is in that ancestor's left subtree.

*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* successor = nullptr;
    
    while (root != nullptr) {
        if (p->val < root->val) {
            // If p is smaller, the current root is a candidate successor
            // but there might be a smaller successor in the left subtree.
            successor = root;
            root = root->left;
        } else {
            // If p is greater or equal, the successor MUST be in the right subtree.
            // We don't update 'successor' here because root is <= p.
            root = root->right;
        }
    }
    
    return successor;
    }
};

// Helper function to insert nodes and build a BST for testing
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

// Helper function to find a specific node in the tree by value
TreeNode* findNode(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return findNode(root->left, val);
    return findNode(root->right, val);
}

int main() {
    Solution sol;

    /* Example Tree:
             5
            / \
           3   6
          / \
         2   4
        /
       1
    */
    TreeNode* root = nullptr;
    vector<int> nodes = {5, 3, 6, 2, 4, 1};
    for (int val : nodes) root = insert(root, val);

    // Test Case: Find successor of node with value 4
    TreeNode* p = findNode(root, 4); 
    TreeNode* result = sol.inorderSuccessor(root, p);

    if (result) {
        cout << "Inorder Successor of " << p->val << " is: " << result->val << endl;
    } else {
        cout << "Inorder Successor of " << p->val << " is: NULL" << endl;
    }

    return 0;
}