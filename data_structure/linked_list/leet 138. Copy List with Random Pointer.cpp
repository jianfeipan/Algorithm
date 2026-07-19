/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:

    /*
    facts:
        deep copy need to understand the relation for random pointer
    idea:
        1 extra data structure, to have the ramdom relation
        2 only one map 
        3 what if we say: don't use any extra memory!
    */

    // 1 put the list into a vector (the order garentee the next relation)
    // have another vector to note the random relation
    // useing a map to find the index of the random
    // time O(N)
    // space: O(N)
    Node* copyRandomList_map_vector(Node* head) 
    {
        if(!head) return nullptr;
        vector<Node*> original; 
        unordered_map<Node*, int> nodeIndex; 
        
        {// construct the data strucutre for noting the relations
            auto current = head;
            int index = 0;
            while(current){
                original.push_back(current);
                nodeIndex[current] = index;
                current = current->next;
                ++index;
            }
        }
        // original             3 7 4 5 
        // map.                 3->0 7-> 1 4->2 5->3
        // randomPointToIndex   
        vector<int> randomPointToIndex(original.size());
        {// find out the random relations
            for(int i = 0; i<original.size(); ++i) 
            {   
                const auto random  = original[i]->random;
                if(random)
                    randomPointToIndex[i] = nodeIndex[random];
                else
                    randomPointToIndex[i] = -1;
            }
        }
        vector<Node*> copied(original.size());
        {//copy
            // construct the node with copied val
            for(int i = 0; i<original.size(); ++i) 
            {
                copied[i] = new Node(original[i]->val);
            }

            // put the next pointer
            for(int i = 0; i<copied.size()-1; ++i) 
            {
                 copied[i]->next = copied[i+1];
            }

            // put the random pointer
            for(int i = 0; i<copied.size(); ++i) 
            {
                const int indexOfrandom = randomPointToIndex[i];\
                if(indexOfrandom!=-1)
                    copied[i]->random = copied[indexOfrandom];
            }
        }
        return copied[0];
    }


    // 2 the first optimisation is to only use map without vector
    // change a way to think, it, you need the same relation, 
    // the relation itself could be modeled by your vector like you did in copyRandomList_map_vector
    // but also this information is already in the original linkedlist
    //what you need to follow this path and do the same for your copied, 
    // using a map<org -> copy> could do this!!!!
    Node* copyRandomList_one_map(Node* head) 
    {
        unordered_map<Node*, Node*> original_to_copied;
        original_to_copied[nullptr] = nullptr;
        {// construct new nodes and put everything in the map
            auto current = head;
            while(current)
            {
                original_to_copied[current] = new Node(current->val);
                current = current->next;
            }
        }

        {// put next and random
            auto current = head;
            while(current)
            {
                auto currentCopy = original_to_copied[current];
                
                currentCopy->next = original_to_copied[current->next];
                currentCopy->random = original_to_copied[current->random];

                current = current->next;
            }
        }

        return original_to_copied[head];
    }


    // 3 what if we say: don't use any extra memory!
    // so basically we are using the maps or the vectors...are for noting the relations,
    // but all relations is already in the linked list
    // and similar idea to org ->copied relation map, linked list has the power to have this link
    // You just use the linked list to do it.
    // 0 -> 1 -> 2 -> 3 -> 4
    // 0 -> 0' ->  1 -> 1'-> 2 -> 2'-> 3 -> 3'-> 4 ->4'
    // so you put the rule:  the original_> next is the copied, and the orig->next->next is the next original element.

    Node* copyRandomList(Node* head) 
    {
        // construct copied nodes
        // it's like the map: copy is org->next
        {// 0 -> 0' ->  1 -> 1'-> 2 -> 2'-> 3 -> 3'-> 4 ->4'
            auto current = head;
            while(current)
            {
                auto nextOrg = current->next;
                current->next = new Node(current->val);
                current->next->next = nextOrg;
                current = nextOrg;
            }
        }

        // put random
        {// copied random = original random->next
            auto current = head;
            while(current)
            {
                auto copied = current->next;
                if(current->random)
                    copied->random = current->random->next;
                current = copied->next;
            }
        }

        // extract the copied
        auto copiedHead = head ? head->next : nullptr;
        {
            auto current = head;
        
            while(current && current->next)
            {
                auto next = current->next;
                current->next = next->next;
                current = next;
            }
        }
        return copiedHead;
    }

};
