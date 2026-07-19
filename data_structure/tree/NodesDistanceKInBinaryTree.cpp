/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 /*
 Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

test sets : 

[3]
3
1
[3]
3
0
[1, 3]
3
0
[1, 11, 12, 111, 112, 121, 122 ]
1
2
[1, 11, 12, 111, 112, 121, 122 ]
11
1
[3,5,1,6,2,0,8,null,null,7,4]
5
2
[0,2,1,null,null,3]
3
3
[0,1,null,3,2]
2
1


 
 
 */
class Solution {
private:
    void countDistanceDown(TreeNode* root, int k, set<int> & kDistanceNodes)
    {
        if(root&&k>=0)
        {
            if(k == 0)
            {
                 kDistanceNodes.insert(root->val) ;
            }
            else if(k>0)
            {
                countDistanceDown(root->left, k-1, kDistanceNodes);
                countDistanceDown(root->right, k-1, kDistanceNodes);
            }
        }
    }
    
    list<TreeNode *> findPath(TreeNode* root, TreeNode* target)
    {
        list<TreeNode *> path;
        if(root)
        {
            if(root == target)
            {
                path.push_back(target);
            }
            else
            {
                if(root->left)
                {
                    list<TreeNode *> leftPath = findPath(root->left, target);
                    if(!leftPath.empty())
                    {
                        path.push_front(root);
                        path.insert(path.end(), leftPath.begin(), leftPath.end());
                    }
                }
                if(root->right)
                {
                    list<TreeNode *> rightPath = findPath(root->right, target);
                    if(!rightPath.empty())
                    {
                        path.push_front(root);
                        path.insert(path.end(), rightPath.begin(), rightPath.end());
                    }
                }
            }
            
        }
        return path;
    }
    
    void countDistanceUp(TreeNode* root, TreeNode* target, int k, set<int> & kDistanceNodes)
    {
        /*
        search target from root and memorize the path in order,
        then you find the distance of nodes in path to the target
        */
        
        list<TreeNode* > path = findPath(root, target);
        
        //from back to front, call countDistanceDown with k - i as distance 
        
        //attention here to have a condition to avoid go down to the same child that you go up
        auto it = path.rbegin();
        countDistanceDown(*it, k, kDistanceNodes);
        
        auto goUpFromChild = it;
        
        ++it;
        --k;
        
        for(; it!=path.rend() && k>=0; --k, ++it)
        {
            auto currentNodeInPath = *it;
            
            cout<<currentNodeInPath->val<< "for"<<k<<endl;
            if(currentNodeInPath)
            {
                if(k==0)
                {
                    countDistanceDown(currentNodeInPath, 0, kDistanceNodes);
                }
                else
                {
                    if(currentNodeInPath->left != *goUpFromChild)
                        countDistanceDown(currentNodeInPath->left, k-1, kDistanceNodes);
                    if(currentNodeInPath->right != *goUpFromChild)
                        countDistanceDown(currentNodeInPath->right, k-1, kDistanceNodes);
                }
            }
            
            goUpFromChild = it;
        }
        
        
        
    }
    
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        
        set<int> kDistanceNodes;
        if(root&&target&&k>=0)
        {
            if(k == 0)
            {
                 return {target->val} ;
            }
            else 
            {
                
                countDistanceUp(root, target, k, kDistanceNodes);
                kDistanceNodes.erase(target->val);
            }
        }
        return vector<int>(kDistanceNodes.begin(), kDistanceNodes.end());
    }
};
