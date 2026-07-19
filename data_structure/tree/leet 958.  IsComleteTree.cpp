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
    bool isCompleteTree(TreeNode* root) 
    {
        /*
        print by a BFS, then check if all nulls are in the end
        */   
        queue<TreeNode*> level;
        
        level.push(root);
        
        while(!level.empty())
        {
            auto current = level.front();level.pop();
            if(current == nullptr) break;
            
            level.push(current->left);level.push(current->right);
        }
        
        //we got the first nullptr
        while(!level.empty())
        {
            auto current = level.front();level.pop();
            if(current!=nullptr) return false;
        }

        return true;
    }
};
