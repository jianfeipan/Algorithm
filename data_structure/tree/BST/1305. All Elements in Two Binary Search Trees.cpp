/**
Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.

 

Example 1:
Input: root1 = [2,1,4], root2 = [1,0,3]
Output: [0,1,1,2,3,4]
Example 2:
Input: root1 = [1,null,8], root2 = [8,1]
Output: [1,1,8,8]

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
    /*
    fact:
        BST: already ordered
        tree to vector
    idea:
        1 How to print one BST to vector? --> vector insert from , insert back, recursively
        2 how to do it with two tree ?? --> failed 

    */

private:
     vector<int> getAllElements(TreeNode * root)
     {
        if(!root) return {};

        vector<int> res =getAllElements(root->left);//KEEP INSERT IN THE BACK! 
        res.push_back(root->val);

        auto right = getAllElements(root->right);
        res.insert(res.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));

        return res;

     }
public:
    vector<int> getAllElements_failed_(TreeNode* root1, TreeNode* root2) {

        if(root1==nullptr)
        {
            return getAllElements(root2);
        }  

        if(root2==nullptr)
        {
            return getAllElements(root1);
        }

        if(root1->val == root2->val)
        {
            vector<int> res = getAllElements(root1->left, root2->left);
            res.push_back(root1->val);
            res.push_back(root2->val);

            auto right = getAllElements(root1->right, root2->right);
            res.insert(res.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));

            return res;
        }

        // you have 2 key points and 3 spaces : 
        
        TreeNode* smallRoot;
        TreeNode* bigRoot;
        if(root1->val < root2->val) 
        {
            smallRoot = root1;
            bigRoot = root2;
        }

        else
        {
            smallRoot = root2;
            bigRoot = root1;
        }

        vector<int> res = getAllElements(smallRoot->left);

        res.push_back(smallRoot->val);

        {
            auto middle = getAllElements(smallRoot->right, bigRoot->left);
            res.insert(res.end(), std::make_move_iterator(middle.begin()), std::make_move_iterator(middle.end()));
        }
        res.push_back(bigRoot->val);
        {
            auto right = getAllElements(bigRoot->right);
            res.insert(res.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));
        }
        return res;
    }

    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {//vector is better....just use two pointers.

        const auto v1 = getAllElements(root1); //O(m)
        const auto v2 = getAllElements(root2); //O(n)
        
        int index1 = 0;
        int index2 = 0;
        
        vector<int> res(v1.size() + v2.size(), 0);


        int i = 0;

        while(index1 < v1.size() && index2 < v2.size()) //O(n+m)
        {
            if(v1[index1] <= v2[index2])
            {
                res[i] = v1[index1];
                ++index1;
            }
            else
            {
                res[i] = v2[index2];
                ++index2;
            }
            ++i;
        }

         while(index1 < v1.size()) 
         {
            res[i] = v1[index1];
            ++index1;
            ++i;
         }  

         while(index2 < v2.size()) 
         {
            res[i] = v2[index2];
            ++index2;
            ++i;
         }  

        return res;
    }
};
