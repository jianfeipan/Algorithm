/*
Given a binary tree root, return the level order traversal of it as a nested list, where each sublist contains the values of nodes at a particular level in the tree, from left to right.

Example 1:



Input: root = [1,2,3,4,5,6,7]

Output: [[1],[2,3],[4,5,6,7]]
Example 2:

Input: root = [1]

Output: [[1]]
Example 3:

Input: root = []

Output: []
Constraints:

0 <= The number of nodes in the tree <= 1000.
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

class Solution {
public:
    // BFS: double queue --> please forget this idea!!!!!!!
    vector<vector<int>> levelOrder_double_queue(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        std::queue<TreeNode*> q1; q1.push(root);
        std::queue<TreeNode*> q2;
        while(!q1.empty() || !q2.empty())
        {
            auto& currentQ = q1.empty()? q2 : q1;
            auto& nextQ = q1.empty()? q1 : q2;

            vector<int> level;
            while(!currentQ.empty()){
                TreeNode* node = currentQ.front();currentQ.pop();
                level.push_back(node->val);
                if(node->left) nextQ.push(node->left);
                if(node->right) nextQ.push(node->right); 
            }   
            res.push_back(level);    
        }

        return res;
    }

    // actually you know the size of the queue, so no need for two queues
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
         vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> q; q.push(root);
        while(!q.empty())
        {
            const auto size = q.size();
            vector<int> level;level.reserve(size);
            for(int i=0; i<size; ++i)
            {
                auto node = q.front(); q.pop();
                level.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right); 
            }
            res.push_back(level);
        }
        return res;
    }
};
