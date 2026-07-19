/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};



[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
[1,null,2,null,3,null]
*/

class Solution {
public:
    Node* flatten(Node* head) {
        Node * current = head;
        while(current)
        {
            auto * nextForLoop = current->next;

            if(current->child)
            {
                auto * next = current->next;
                auto * flattenedChild = flatten(current->child);
                current->next = flattenedChild;
                current->child = nullptr;//remember to put child nullptr
                flattenedChild->prev = current;

                auto * end = getEnd(current->next);

                end->next = next;
                if(next)
                    next->prev = end;
            }
            current = nextForLoop;
        }
        
        return head;
    }
    
private:
    Node * getEnd(Node * node)
    {
        while(node && node->next)
        {
            node=node->next;
        }
        return node;
    }
    
};
