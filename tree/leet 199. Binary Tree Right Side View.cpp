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
    vector<int> rightSideView(TreeNode* root) {
        //idea is a BFS , with right child first and take the top int he queue for each level
        vector<int> result;
        if(!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            result.push_back(q.front()->val);
            
            const size_t currentLevelSize = q.size();
            for(size_t i = 0; i < currentLevelSize; ++i)
            {
                auto * node = q.front();q.pop();
                if(node->right) q.push(node->right);//right first , because we want to get the front 
                if(node->left) q.push(node->left);
            }
        }
        return result;
    }
};
