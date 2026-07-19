#include <algorithm>
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BST {
    
private:
    TreeNode* mostLeft(TreeNode* root)
    {
        if(!root->left)
            return root;
        else
            return mostLeft(root->left);  
    }
    
    TreeNode* mostRight(TreeNode* root)
    {
        if(!root->right)
            return root;
        else
            return mostRight(root->right);  
    }
    bool isValidBSTHelper(TreeNode* root, TreeNode* lefthigh, TreeNode* rightlow)
    {
        if(root == nullptr){
            return true;
        }
        if(lefthigh != nullptr && root->val <= lefthigh->val){
            return false;
        }
        if(rightlow != nullptr && root->val >= rightlow->val){
            return false;
        }
        return isValidBSTHelper(root->right, root, rightlow) && isValidBSTHelper(root->left, lefthigh, root);
    }
    

    //from current  to children to find limits 
    bool isValidBST_1(TreeNode* root) 
    {
        bool isValide = false;
        if(root)
        {
            isValide = true;
        
            if(root->left)
            {
                TreeNode* mostRightNode = mostRight(root->left);
                isValide = isValide && ((mostRightNode->val)<root->val) && isValidBST(root->left);
                
            }

            if(root->right)
            {
                TreeNode* mostLeftNode = mostLeft(root->right);
                isValide = isValide && ((mostLeftNode->val)>root->val) && isValidBST(root->right);
            }
        }
        return isValide;
    }

    TreeNode* findMax(TreeNode* root)
    {
        if(root == nullptr)
            return nullptr;
        if(root->right!=nullptr)
            return findMax(root->right);
        else
            return root;
    }

    int hight(TreeNode * root)
    {
        if(root == nullptr)
            return 0;
        return std::max(hight(root->left), hight(root->right)) +1;

    }

public:
    //faster solution: from current to parent to find limits
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root, nullptr, nullptr); 
    }
	
	
	TreeNode * search(TreeNode * root, int val)
	{
		if(root == nullptr)
			return nullptr;
		if(val == root->val)
			return root;
		else if(val < root->val)
			return search(root->left, val);
		else if(val > root->val)
			return search(root->right, val);
	}
	
	TreeNode * search2(TreeNode * root, int val)
	{
		TreeNode *  current = root;
		while(current != nullptr)
		{
			if(val == current->val)
				return current;
			else if(val < current->val)
				current = current->left;
			else if(val > root->val)
				current = current->right;
		}
		
		return nullptr;
	}
	
	void insert(TreeNode * root, int val)
	{
		if(root == nullptr)
			return;
		
		if(val == root->val)
			return;
		else if(val < root->val)
		{
			if(root->left == nullptr)
			{
				root->left = new TreeNode(val);
			}
			else{
				insert(root->left, val);
			}
		}
		else if(val > root->val)
		{
			if(root->right == nullptr)
			{
				root->right = new TreeNode(val);
			}
			else{
				insert(root->right, val);
			}
		}
	}
	
    //Attention here the return type, that returns the tree after removing the node, which allows to  recusivly call the remove function
	TreeNode * remove(TreeNode * root, int val)
    {  
        if(root==nullptr)
            return nullptr;
        if(root->val<val)
        {
            //attention the return, to update left side
            root->left = remove(root->left, val);
        }
        else if(root->val>val)
        {
            //attention the return, to update left side
            root->right = remove(root->right, val);
        }
        else
        {
            if(root->left!=nullptr && root->right!=nullptr)
            {
                //Here we can put left branch's largest value then remove that one
                //or we can put right branch's smallest value then remove that one
                TreeNode * leftBranchLargest = findMax(root->left);

                root->val = leftBranchLargest->val;

                root->left = remove(root->left, root->val );
            }
            else
            {
                if(root->left!=nullptr)
                    root = root->left;
                else if(root->right!=nullptr)
                    root = root->right;
                else
                    root = nullptr;//this nullptr will be return to uper level to remove current node
            }
        }
        return root;
    }
	

    bool isBanlanced(TreeNode * root)
    {
        if(root == nullptr)
            return true;
        int res =abs(hight(root->left) - hight(root->right));
        return res < 2 && isBanlanced(root->left) && isBanlanced(root->right);//Notice here we recomputed hight value in sub trees
    }

    //To avoid the recomputation of hight in sub trees, better idea is to from bottom to top
    static int isBanlancedHelper(TreeNode* root) {
        if(root == nullptr)
            return 0;

        int lheight = isBanlancedHelper(root->left);
        if(lheight == -1)
            return -1;//stop to recusivly up computings because it's already not balanced

        int rheight = isBanlancedHelper(root->right);
        if(rheight == -1)
            return -1;

        if(abs(lheight - rheight) > 1) {
            return -1;
        }

        return std::max(lheight, rheight) + 1;
    }

    bool isBanlanced2(TreeNode * root)
    {
        return isBanlancedHelper(root)!=-1;;
    }
 

};
