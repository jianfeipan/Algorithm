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
class Solution {//from leaves to root: every leaf gives it's possible sums, and all node has all possible nodes, then count
private:    
    size_t count = 0;
    
    const vector<int> possibleSumsFromSubTree(TreeNode * root, int target)
    {
        if(!root)
            return {};
        
        vector<int> nodePossibleSums{root->val};
        //cout<< root->val << ": " <<root->val<< "?"<<target<<endl;
        if(target == root->val)
            count++;
        
        

        if(root->left)
        {
            const vector<int> &  leftPossibleSums = possibleSumsFromSubTree(root->left, target);
            nodePossibleSums.reserve(nodePossibleSums.size() + leftPossibleSums.size());
            for(int leftPossibleSum : leftPossibleSums)
            {
                const int sum = leftPossibleSum + root->val;
                if(target == sum)
                    count++;
                nodePossibleSums.push_back(sum);
            }
        }
        
        if(root->right)
        {
            const vector<int> &  rightPossibleSums = possibleSumsFromSubTree(root->right, target);
             nodePossibleSums.reserve(nodePossibleSums.size() + rightPossibleSums.size());
            for(int rightPossibleSum : rightPossibleSums)
            {
                const int sum = rightPossibleSum + root->val;
                if(target == sum)
                    count++;
                nodePossibleSums.push_back(sum);
            }
        }
        
        return nodePossibleSums;
    }
    
public:
    int pathSum(TreeNode* root, int targetSum) {
        //recusive list of possible sums of sub tree
        count = 0;
        possibleSumsFromSubTree(root, targetSum);
        
       
        return count;
    }
};

class Solution_root_to_leaves {
  /*from root to leaves: sum from root to leave, and use a map to note "removable sum" 
  for exmale: 1->2->3->4
  
  for node 3, we have total sum of 1+2+3 = 6, and in map, we have {0=1, 1=1, 3=1}
  we could use 6 to minus every keys in map to have possible sums : 
  6 - 0 = (node 1 + node 2 + node 3) = 6
  6 - 1 = (node 2 + node 3) = 5
  6 - 3 = node3 =3
    
  */
public:
    
    unordered_map<int,int> m;
    int ans=0;
    
    void rek(TreeNode* root, int targetSum, int sum)
    {
        if (!root) return;
        
        sum+=root->val;
        if (m.find(sum-targetSum)!=m.end())
        {
            ans+=m[sum-targetSum];
        }
        m[sum]++;//in this sub tree
        rek(root->left,targetSum,sum);
        rek(root->right,targetSum,sum);
        m[sum]--;//getting out this sub tree and this sum is no more there
    }
    
    int pathSum(TreeNode* root, int targetSum) {
        m[0]=1;
        rek(root,targetSum,0);
        return ans;
    }
};
