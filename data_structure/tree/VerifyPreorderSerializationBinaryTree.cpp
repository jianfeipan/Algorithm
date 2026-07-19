#include<iostream>
#include<vector>
#include<sstream>
#include <istream>
#include <stack>


class Solution {
    
private:
     struct TreeNode {
         string val;
         TreeNode *left;
         TreeNode *right;
         TreeNode() : val(""), left(nullptr), right(nullptr) {}
         TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
         TreeNode(string x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     };
    
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
        
        if(i<nodes.size()-1)
            return nullptr;
        
        return root;
    }
    
    bool isValideTree(TreeNode * root)
    {
        if(root)
        {
            if(root->val == "#")
            {
                return root->left==nullptr 
                    && root->right==nullptr;
            }
            else
            {
                return isValideTree(root->left) 
                    && isValideTree(root->right);
            }
        }
        return false;
    }
    
    
public:
    

    
    bool isValidSerialization_slow(string preorder) {
        
       vector<string> nodes;
       std::stringstream ss(preorder);
       while(ss.good()) {
          string node;
          std::getline(ss, node, ','); //get first string delimited by comma
          if(node.empty())
              return false;
          nodes.push_back(node);
       }
        const size_t size = nodes.size();
        
        if(size<3)
        {
            return size==1 && nodes[0]=="#";
        }
        else
        {
            if(nodes[size-1]=="#" && nodes[size-2]=="#")
            {
                TreeNode * tree = constructTree(nodes);
                return isValideTree(tree);
            }
            else
            {
                return false;
            }
            
        }
        
    }
    //a solution only check the number of nodes
    //if we got a not # node, we should have at least 2 more nodes
    bool isValidSerialization(string preorder) {
        vector<string> nodes;
       std::stringstream ss(preorder);
       while(ss.good()) {
          string node;
          std::getline(ss, node, ','); //get first string delimited by comma
          if(node.empty())
              return false;
          nodes.push_back(node);
       }
        
        const size_t size = nodes.size();
        if(size<3)
        {
            return size==1 && nodes[0]=="#";
        }
        else
        {
            if(nodes[0]!="#" && nodes[size-1]=="#" && nodes[size-2]=="#")
            {
                int numb = 0;
                for(size_t i = 0; i<size-1;i++)
                {
                    if(nodes[i] != "#")
                    {
                        numb++;
                    }
                    else
                    {
                        numb--;
                    }
                    if(numb<=-1)
                        return false;
                }

                return numb == 0;
            }
            else
            {
                return false;
            }
            
        }
        
        
    }
};
