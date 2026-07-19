/*
ou are given the root of a binary tree with n nodes, where each node is uniquely assigned a value from 1 to n. You are also given a sequence of n values voyage, which is the desired pre-order traversal of the binary tree.
[1]
[1]
[1,2]
[2,1]
[1,2,3]
[2,1,3]
[1,2,3]
[2,3,1]
[1,2,3]
[1,3,2]
[1,2,3]
[1,2,3]
[1,2,3,null,null,4,5]
[1,3,4,5,2]
[1,2,null,3]
[1,3,2]

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
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) 
    {
        if(root->val==voyage[0])
        {
            int from = 0;
            if(tryToFlipAndMatch(*root, voyage, from))
            {
                return flippedRoots;
            }
        }
        return {-1};
    }
    
private:
    void flip(TreeNode & root)
    {
        auto temp = root.left;
        root.left = root.right;
        root.right = temp;
    }
    
    bool tryToFlipAndMatch(TreeNode & root, const vector<int>& voyage, int & from)
    {
        //cout<< root.val<< ":" << from<<endl;
        
        if(root.left)
        {
            if(root.left->val == voyage[from+1])
            {
                from++;
                if(!tryToFlipAndMatch(*root.left, voyage, from))
                    return false;
            }
            else
            {
                flip(root);
                flippedRoots.push_back(root.val);
                if(root.left)
                {
                    if(root.left->val == voyage[from+1])
                    {
                        from++;
                        if(!tryToFlipAndMatch(*root.left, voyage, from))
                            return false;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }

        if(root.right)
        {
            if(root.right->val == voyage[from+1])
            {
                from++;
                if(!tryToFlipAndMatch(*root.right, voyage, from))
                    return false;
            }
            else
            {
                return false;
            }
        }
        
        return true;

    }
    
    vector<int> flippedRoots;
};
