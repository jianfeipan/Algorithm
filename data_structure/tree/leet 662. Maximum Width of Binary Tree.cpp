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
    int widthOfBinaryTree(TreeNode* root) 
    {
        /*
        BFS level by level
        */        
        int maxWidth = 0;
        
        queue<pair<TreeNode*, int>> level;
        if(root) level.push({root, 0});
        
        while(!level.empty())
        {
            int size = level.size();
            
            int left = INT_MAX;
            int right = 0;
            
            
            int startIndex = level.front().second;
            while(size-->0)
            {
                const auto & current = level.front();
                auto * node = current.first; 
                int pos = current.second - startIndex;//Offset of start point to avoid int over flow              
              
                
                left = min(left, pos);
                right = max(right, pos);
                
                if(node->left) level.push({node->left, pos*2});
                if(node->right) level.push({node->right, pos*2+1});
                
                level.pop();
            }
            maxWidth = max(maxWidth, right - left + 1);
        }
        
        return maxWidth;
        
    }
};
