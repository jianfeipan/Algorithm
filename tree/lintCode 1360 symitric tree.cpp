/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: root of the given tree
     * @return: whether it is a mirror of itself 
     */
    bool isSymmetric_recusive(TreeNode * root) {
        if(!root) return true;
        return isMirror(root->left, root->right);
    }

    bool isSymmetric(TreeNode * root) {
        //Using a queue to check the tree level by level
        if(!root) return true;

        std::deque<TreeNode*> level ({root->left, root->right});

        while(!level.empty())
        {
            std::deque<TreeNode*> nextLevel;
            while(!level.empty())
            {

                TreeNode* left = level.front();
                level.pop_front();
                TreeNode* right = level.back();
                level.pop_back();

                if(left && right && (left->val == right->val))
                {
                    nextLevel.push_front(left->left);
                    nextLevel.push_front(left->right);
                    nextLevel.push_back(right->right);
                    nextLevel.push_back(right->left);
                } 
                else{
                    if(left || right) 
                        return false;
                }
            }
            level = nextLevel;
        }


        return true;
    }
private:
    bool isMirror(TreeNode * left, TreeNode * right)
    {
        if(!left && !right)
            return true;
        else if(left && right)
        {
            return (left->val == right->val) && isMirror(left->left, right->right) && isMirror(left->right, right->left);    
        }
        else
            return false;
    }
};
