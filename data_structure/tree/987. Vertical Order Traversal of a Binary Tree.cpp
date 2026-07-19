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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        //BFS use a struct to store the nodes' coordinates
        
        map<int, map<int, multiset<int>>> coordinates;
        
        queue<pair<TreeNode*, pair<int, int>>> level;
        level.push({root, {0,0}});
        
        while(!level.empty())
        {
            const size_t size = level.size();
            
            for(size_t i=0; i<size; ++i)
            {
                const auto & node = level.front();
                const int col = node.second.first;
                const int lin = node.second.second;
                TreeNode * current = node.first;
                
                //cout<<current->val<<endl;
                
                coordinates[col][lin].insert(current->val);
                
                if(current->left)
                    level.push({current->left, {col-1, lin+1}});
                
                if(current->right)
                    level.push({current->right, {col+1, lin+1}});
                
                level.pop();
            }
        }
        
        vector<vector<int>> verticalNodes;verticalNodes.reserve(coordinates.size());

        size_t linCount= 0;
        for(const auto & col : coordinates)
        {
            vector<int> currentCol;currentCol.reserve(col.second.size());
            
            for(const auto & lin : col.second) currentCol.insert(currentCol.end(), lin.second.begin(), lin.second.end());
            
            verticalNodes.push_back(currentCol);
        }
        
        return verticalNodes;
    }
};
