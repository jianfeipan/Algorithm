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
        queue<TreeNode*> bfs;
        if(root) bfs.push(root);
        vector<int> right_side;
        while( !bfs.empty() ) {
            right_side.push_back(bfs.back()->val);
            const auto size = bfs.size();
            for(int i=0; i<size; ++i) {
                auto cur = bfs.front();bfs.pop();
                if( cur->left ) bfs.push(cur->left);
                if( cur->right ) bfs.push(cur->right);
            }
        }
        return right_side;
    }
};

