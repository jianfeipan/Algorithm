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
#include <vector>
#include <unordered_map>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // preorder: m->l->r
    // inorder: l->m->r
    TreeNode* _buildTree(const vector<int>& preorder, 
                        int pstart, int pend,
                        const vector<int>& inorder,
                        int istart, int iend,
                        const unordered_map<int, int>& inorderMap)
    {
        if (pstart > pend || istart > iend) return nullptr;
        // we need to find index of end of left subtree in preorder and index of root in inorder
        int rootVal = preorder[pstart];
        int irootIndex = inorderMap.at(rootVal);
        int leftTreeSize = irootIndex - istart;


        TreeNode* root = new TreeNode(preorder[pstart]);
        root->left = _buildTree(preorder, pstart+1, pstart+leftTreeSize,
                                inorder, istart, irootIndex-1, inorderMap);

        root->right = _buildTree(preorder, pstart+leftTreeSize+1, pend,
                                inorder, irootIndex+1, iend, inorderMap);        
        return root;                
    }


    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        // Build hash map for O(1) lookup of inorder indices
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return _buildTree(preorder, 0, preorder.size()-1,
                          inorder, 0, inorder.size()-1, inorderMap);
        
    }
};
/*
this is a more iterative approach, the while actually can be reused to build the tree
iterating over preorder, it's r-> l -> r, and even inside the l, the first is the l (if not missing)

so if the tree is full, we will keep doing current->left = preorder[i]
until we find the most left node, then we will start to build the right subtree
and the most left node is actually the first node in the inorder
->so while(i<n && curr->val != inorder[j]) we keep building left subtree, until we find the most left node
->when we rach the most left node, we start to build the right subtree


*/

class Solution2 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* head = new TreeNode(0);
        TreeNode* curr = head;
        int i = 0, j = 0, n = preorder.size();

        while (i < n && j < n) {
            // we start to build the right subtree: read the next two while block will expalin why we start from this right subtree
            curr->right = new TreeNode(preorder[i], nullptr, curr->right);
            curr = curr->right;

            /*           
            pre = [1 2 3 4]
            in =  [2 1 3 4]
            0
             \
              1

            */

            i++;
            while (i < n && curr->val != inorder[j]) { // beofore the most left node, we keep building left subtree
                curr->left = new TreeNode(preorder[i], nullptr, curr);
                // using the right pointer to point to parent, so we can easily go back to build right subtree after we find the most left node
                curr = curr->left;
                i++;
            }
            /*

            0
             \
              1
             /
            2
            */
            j++; // we find the most left node, we start to build right subtree
            // curr->right is actually the parent of curr, curr->right->val == inorder[j] makes sure we are still going back the the root from left
            // when curr->right->val != inorder[j] : we reached the first right subtree
            while (curr->right && j < n && curr->right->val == inorder[j]) {
                TreeNode* prev = curr->right;
                curr->right = nullptr; // correction of the right
                curr = prev;//going up the the parent
                j++;
            }
        }
        return head->right;
    }
};
