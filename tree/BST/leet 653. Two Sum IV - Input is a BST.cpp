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
    
    /*
    idea2:
    inOrder travaersal to put them in a sorted vector, then use two pointer O(N)
    */
    bool findTarget_vector_two_pointer(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums);
        return findTargetInSortedArray(nums, k);
    }

    
    /*
    idea1:
    recusive for every node, we seache the other point, no duplication in a BST
    */
    
    bool findTarget(TreeNode* root, int k) //O(NlogN)
    {
        if(!root) return false;
        
        return findTarget(root, root, k);
        
    }
    
private:
    bool findTarget(TreeNode* current, TreeNode* root, int k) 
    {
        if(!current) return false;
        
        if(current->val != k-(current->val))//avoid found it self
        {
            auto secondNode = search(root, k-(current->val));
            if(secondNode) return true;
        }
        return findTarget(current->left, root, k) 
            || findTarget(current->right, root, k);
        
    }

    TreeNode* search(TreeNode* root, int k) 
    {
        if(root)
        {
            if(root->val == k) return root;
            else if(root->val < k) 
                return search(root->right, k);
            else
                return search(root->left, k);
        }
        else
            return nullptr;
    }
    
    void inorder(TreeNode* node, vector<int>& nums) {
        if (!node) return;
        inorder(node->left, nums);
        nums.push_back(node->val);
        inorder(node->right, nums);
    }

    bool findTargetInSortedArray(vector<int> a, int target) {
        for (int i = 0, j = a.size() - 1; i < j;) {
            int sum = a[i] + a[j];
            if (sum == target) {
                return true;
            }
            else if (sum < target) {
                i++;
            }
            else {
                j--;
            }
        }

        return false;
    }

};
