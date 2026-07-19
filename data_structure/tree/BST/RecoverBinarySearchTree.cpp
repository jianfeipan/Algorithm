class RecoverBinarySearchTree {
  //https://leetcode.com/problems/recover-binary-search-tree
public:
    TreeNode* swap1 = NULL, *swap2 = NULL, *pred=NULL;
    void recoverTree(TreeNode* root) {
        dfs(root);
        swap(swap1,swap2);
    }
    void dfs(TreeNode* root)
    {
        if(!root)
            return;
        dfs(root->left);
        if(pred!=NULL&&root->val < pred->val)
        {
            swap2 = root;// from left to right, so swap 1 is the smallest and not change, swap 2 can be updated every time we found a new incorrect order
            if(!swap1) // if swap1 is found the second time, we can stop because we only have one paire that was swaped
                swap1=pred;
            else
                return;
        }
        pred = root; // to note the last element in left children
        dfs(root->right);
    }
    void swap(TreeNode* node1, TreeNode* node2)
    {
        int tmp = node1->val;
        node1->val = node2->val;
        node2->val = tmp;
    }
};
