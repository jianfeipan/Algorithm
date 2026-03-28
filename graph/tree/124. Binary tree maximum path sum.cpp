/*
Given the root of a non-empty binary tree, return the maximum path sum of any non-empty path.

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes has an edge connecting them. A node can not appear in the sequence more than once. The path does not necessarily need to include the root.

The path sum of a path is the sum of the node's values in the path.

Example 1:



Input: root = [1,2,3]

Output: 6
Explanation: The path is 2 -> 1 -> 3 with a sum of 2 + 1 + 3 = 6.

Example 2:



Input: root = [-15,10,20,null,null,15,5,-5]

Output: 40
Explanation: The path is 15 -> 20 -> 5 with a sum of 15 + 20 + 5 = 40.

Constraints:

1 <= The number of nodes in the tree <= 1000.
-1000 <= Node.val <= 1000

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

class Solution 
{
/*
facts:
    1.one node can be taken or not, we don't neccessarily from leaf to leaf
    2.for any path, the "identity" of the path is the root
    3. node val can be negative -> std::max(0, 
idae:
    1 recursivly traversal all nodes, compute the max sum to it's leaf

complexity:
time O(n)
stack usage O(n)


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
private:
    // max  from root to left or right must include root
    int maxFrom(TreeNode* root, int& globalMaxSum){
        if(!root) return 0;
        int curr = root->val;
        int l = max(0, // if l < 0, we don't take it
                    maxFrom(root->left, globalMaxSum));
        int r = max(0, 
                    maxFrom(root->right, globalMaxSum));
        globalMaxSum = max(globalMaxSum, l+curr+r);
        return max(l+curr, r+curr);

    }

public:
    int maxPathSum(TreeNode* root) {
        int globalMaxSum = INT_MIN; 
        maxFrom(root, globalMaxSum);
        return globalMaxSum;
    }
};

};
