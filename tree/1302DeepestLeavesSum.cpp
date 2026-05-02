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




Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
Example 2:

Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 19

 
 */
class Solution {

private:
    int bfs(TreeNode* root){
        int sum = 0;

        vector<TreeNode*> q;
        if(root)
            q.push_back(root);
        
        
        while(!q.empty())
        {
            vector<TreeNode*> nextLeve;

            for(auto * current : q)
            {
                sum+=current->val;
                if(current->left) nextLeve.push_back(current->left);
                if(current->right) nextLeve.push_back(current->right);
            }
            q.clear();
            if(!nextLeve.empty())
            {
                sum = 0;

                q = std::move(nextLeve);
            }

        }

        return sum;
    }

    void dfs_internal(TreeNode* current, int depth, int & max_depth, int & ans)
    {
        if(current) 
        {
            dfs_internal(current->left, depth +1, max_depth, ans);
            dfs_internal(current->right, depth +1, max_depth, ans);

            if(depth==max_depth)
            {
                ans+=current->val;
            }
            else if(depth>max_depth)
            {
                max_depth = depth;
                ans = current->val;
            }
        }
    }

    int dfs(TreeNode* root) 
    {
        int max_depth = -1;
        int ans = 0;
        
        dfs_internal(root, 0, max_depth, ans);


        return ans;
    }


public:
    int deepestLeavesSum(TreeNode* root) {
        return dfs(root);
    }
};
