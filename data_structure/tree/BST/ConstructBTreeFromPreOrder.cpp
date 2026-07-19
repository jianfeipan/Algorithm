 
/*
use # as null node
*/



TreeNode * constructTree(const vector<string> & nodes)
    {
        if(nodes.empty())
            return nullptr;
        
        TreeNode * root = new TreeNode(nodes[0]);
        
        std::stack<TreeNode *> stack;
        
        stack.push(root);
        int i = 1;
        for(; i<nodes.size() && !stack.empty() ;i++)
        {
            const string & val = nodes[i];
            
            TreeNode * last = stack.top();
            
            if(last->left == nullptr)
            {
                last->left = new TreeNode(val);
                if(val=="#")
                {
                    
                }
                else
                {
                    stack.push(last->left);
                }
            }
            else if(last->right == nullptr)
            {
                last->right = new TreeNode(val);
                stack.pop();
                if(val=="#")
                {
                }
                else
                {
                    stack.push(last->right);
                }
            }
            else
            {
                
            }
        }
        
        if(i<nodes.size()-1)//unvalide preorder list
            return nullptr;
        
        return root;
    }

//recusive solution

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
private:
    size_t findMaxIndexSmallerThan(const vector<int>& preorder, int rootVal, size_t from, size_t to)
    {
        size_t index = from;
        
        for(; index< preorder.size(); ++index)
        {
            if(preorder.at(index)>rootVal)
            {
                break;
            }
        }
        //cout<<"index : "<<index-1<<endl;
        return index-1;
    }
    
    TreeNode* bstFromPreorder(const vector<int>& preorder, int from,  int to)
    {   TreeNode* root = nullptr;    
        if(from<preorder.size() && to >= from)
        {
            //cout<<from << "to "<<to<<endl;
            root = new TreeNode(preorder[from]);
            if(from < to)
            {
                size_t leftTreeTo = findMaxIndexSmallerThan(preorder, root->val, from+1, to);
                root->left = bstFromPreorder(preorder, from+1, leftTreeTo);
                root->right = bstFromPreorder(preorder, leftTreeTo+1, to);
            }
        }
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return bstFromPreorder(preorder, 0, preorder.size()-1);
    }
};
