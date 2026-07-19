/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) 
    {
        if(!root) return nullptr;//throw invalid_argument("empty root");
        
        queue<Node*> level;
        
        level.push(root);
        
        while(!level.empty())
        {
            int size = level.size();
            Node * next = nullptr;
            while(size-->0)
            {
                Node * current = level.front(); level.pop();
                current->next = next;
                next = current;
                
                if(current->right) level.push(current->right);//front right to left
                if(current->left) level.push(current->left);
            }
        }
        
        return root;
    }
};
