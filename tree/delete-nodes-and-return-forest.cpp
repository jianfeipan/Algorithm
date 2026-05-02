/*

Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

[2]
[1]
[1]
[1]
[1,2,3]
[2,3]
[1,2,3,4,5,6,7]
[3,5]
 
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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> nodes({root});
        
        
        for(int i : to_delete)
        {
            delNodes(nodes, i);
        }

        
        return nodes;
    }
    
private:
    void delNodes(vector<TreeNode*> & nodes, int to_delete)
    {
        const size_t nodesSize = nodes.size();
        bool deleted = false;
        for(size_t i = 0; i<nodesSize && !deleted; ++i)
        {
            TreeNode * res = deleteNode(nodes[i], to_delete, deleted, nodes);
            nodes[i] = res;
        }
        
        nodes.erase(std::remove_if(nodes.begin(), nodes.end(),[](const TreeNode * n) { return n==nullptr; }),
                    nodes.end());
    }                     
    
    TreeNode * deleteNode(TreeNode * root, int to_delete, bool & deleted, vector<TreeNode*> & nodes)
    {
        if(root && !deleted)
        {
            if(root->val == to_delete)
            {
                deleted = true;
                if(root->left)
                    nodes.push_back(root->left);

                if(root->right)
                    nodes.push_back(root->right);
                return nullptr;

            }
            else
            {
                root->left = deleteNode(root->left, to_delete, deleted, nodes);
                root->right = deleteNode(root->right, to_delete, deleted, nodes);
            }
        }
        return root;
    }
    
};
