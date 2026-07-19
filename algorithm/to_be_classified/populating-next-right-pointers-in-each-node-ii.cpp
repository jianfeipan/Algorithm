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
private:
    std::queue<Node*> levelA;
    std::queue<Node*> levelB;
    //double queue seems easy to implement, but can be replace by one queue and a counter, which read the initial size of the queue, then do a for loop instead of looping all elements in a queue.
    
    static Node * pop(std::queue<Node*> & currentLevel, std::queue<Node*> & nextLevel )
    {
        Node * current = currentLevel.front();
        currentLevel.pop();
        if(current->left)
        {
            nextLevel.push(current->left);
        }
        if(current->right)
        {
            nextLevel.push(current->right);
        }
        return current;
    }
    
public:
    Node* connect(Node* root) 
    {
        vector<vector<int>> levels;
        if(root)
        {
            root->next=nullptr;
            
            levelA.push(root);
            while(!levelA.empty() || !levelB.empty())  
            {

                if(!levelA.empty())
                {
                    Node * current = pop(levelA, levelB);
                    
                    while(!levelA.empty())
                    {
                        Node * next = pop(levelA, levelB);
                        
                        current->next = next;
                        current = next;
                    }
                }
                else
                {
                    Node * current = pop(levelB, levelA);

                    while(!levelB.empty())
                    {
                        Node * next = pop(levelB, levelA);
                        current->next = next;
                        current = next;
                    }
                }

            }
        }
        return root;
        
    }

};

