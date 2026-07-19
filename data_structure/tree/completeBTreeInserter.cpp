/*
A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.

Design an algorithm to insert a new node to a complete binary tree keeping it complete after the insertion.

["CBTInserter","get_root"]
[[[1,2]],[]]
["CBTInserter","insert","get_root"]
[[[1]],[2],[]]
["CBTInserter","insert","insert","get_root"]
[[[1]],[2],[2],[]]
["CBTInserter","insert","insert", "insert","get_root"]
[[[1]],[2],[2],[3],[]]
["CBTInserter", "insert", "insert", "get_root"]
[[[1, 2]], [3], [4], []]
["CBTInserter","insert","insert","get_root"]
[[[1,2,3,4,5,6]],[7],[8],[]]

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
class CBTInserter {
public:
    CBTInserter(TreeNode* root) : _root(root){
        uncompleteNode = _root;
        if(_root)
            nodesQueue.push_back(_root);
    }
    
    int insert(int val) {
        TreeNode * newNode = new TreeNode(val);
        
        findFirstUncompleteNode();
        
        if(!uncompleteNode->left)
            uncompleteNode->left = newNode;
        else if(!uncompleteNode->right)
            uncompleteNode->right = newNode;
        return uncompleteNode->val;
    }
    
    TreeNode* get_root() {
        return _root;
    }
private:
    bool isComplet(TreeNode & root)
    {
        return root.left&&root.right;
    }
    
    void findFirstUncompleteNode()
    {
        
        
        while(!nodesQueue.empty())
        {
            const size_t currentLevelSize = nodesQueue.size();
                  
            auto it = nodesQueue.begin();
            //cout<<  "in queue : "<< currentLevelSize << "nodes" <<endl;

            for(; it!=nodesQueue.end(); ++it)
            {
                auto node = *it;
                
                //cout<< node->val<<endl;
                
                if(!isComplet(*node))
                {
                    uncompleteNode = node;
                    break;
                }
                
            }   
            
            if(it!= nodesQueue.end())
            {
                break;//we found the last complete level in the queue and the uncomplet node position
            }
            else
            {
                for(size_t i = 0; i<currentLevelSize; ++i)
                {
                    auto node = nodesQueue.front();
                    nodesQueue.pop_front();
                    
                    nodesQueue.push_back(node->left);
                    nodesQueue.push_back(node->right);
                }  
            }
            
        }
    }
    
    TreeNode* _root;
    std::list<TreeNode*> nodesQueue;
    TreeNode* uncompleteNode;

};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
