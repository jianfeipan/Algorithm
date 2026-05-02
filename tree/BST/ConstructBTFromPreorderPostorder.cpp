/*

Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.

If there exist multiple answers, you can return any of them.


[1]
[1]
[1,2,3]
[2,3,1]
[1,2,4,5,3,6,7]
[4,5,2,6,7,3,1]



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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        
        return constructFromPrePost(preorder, postorder, 0, preorder.size()-1, 0, postorder.size()-1);
    }
    
private:
    TreeNode* constructFromPrePost(const vector<int>& preorder, 
                                   const vector<int>& postorder, 
                                   int preFrom,
                                   int preTo,
                                   int postFrom,
                                   int postTo) {
        if(preFrom>=0 && postFrom>=0 && preTo<=preorder.size()-1 && postTo<=postorder.size()-1)
        {
            if(preFrom == preTo && postFrom==postTo)
            {
                //cout<<"create"<<preorder[preFrom]<<endl;;
                return new TreeNode(preorder[preFrom]);
            }
            else if(preFrom<preTo && postFrom<postTo)
            {
                TreeNode * root = new TreeNode(preorder[preFrom]);
                
                int nextChildInPreOrder = preFrom+1;
                int nextChild = preorder[nextChildInPreOrder];
                
                //find this child's index in post order
                int nextChildInPostOrder = postFrom;
                for(; nextChildInPostOrder<=postTo; ++nextChildInPostOrder)
                {
                    if(postorder[nextChildInPostOrder] == nextChild)
                    {
                        break;
                    }
                }
                
                int nextChildSubTreeSize = nextChildInPostOrder - postFrom +1;
                
                //cout<<nextChildInPreOrder<<"-"<<nextChildInPreOrder + nextChildSubTreeSize - 1<<endl;
                //cout<<postFrom<<"-"<<nextChildInPostOrder<<endl;
                
                root->left = constructFromPrePost(preorder, 
                                                  postorder, 
                                                  nextChildInPreOrder, 
                                                  nextChildInPreOrder + nextChildSubTreeSize - 1,
                                                  postFrom,
                                                  nextChildInPostOrder
                                                 );
                
                root->right = constructFromPrePost(preorder, 
                                                  postorder, 
                                                  nextChildInPreOrder + nextChildSubTreeSize, 
                                                  preTo,
                                                  postFrom + nextChildSubTreeSize,
                                                  postTo-1
                                                 );
                return root;
                
            }
        }
        return nullptr;
    }

};
