

/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.


facts:
    1. single lined-list
    2 have the head as input
    3 need to access the last nodes frequently 

idea:
    1 I will need a vector to access last pointers.
    2 two things i need to do:
        - 1->next to n
        - n->next to 2
pay atention:
    vector index  boundry !!




*/
 
/*
You are given the head of a singly linked-list.

The positions of a linked list of length = 7 for example, can intially be represented as:

[0, 1, 2, 3, 4, 5, 6]

Reorder the nodes of the linked list to be in the following order:

[0, 6, 1, 5, 2, 4, 3]

Notice that in the general case for a list of length = n the nodes are reordered to be in the following order:

[0, n-1, 1, n-2, 2, n-3, ...]

You may not modify the values in the list's nodes, but instead you must reorder the nodes themselves.

Example 1:

Input: head = [2,4,6,8]

Output: [2,8,4,6]
Example 2:

Input: head = [2,4,6,8,10]

Output: [2,10,4,8,6]
Constraints:

1 <= Length of the list <= 1000.
1 <= Node.val <= 1000


*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


class Solution {
public:
    //find the middle node, 0 1 2 [3] 4 5 6 
    // have two list: 0 1 2 3 and 4 5 6
    // reverse the 4 5 6 to 6 5 4
    // merge with two pointers
    void reorderList(ListNode* head){
        // find middle: using two pointers with speed = 1 and speed = 2
        auto current = head;
        auto quickerCurrent = head;
        while(quickerCurrent && quickerCurrent->next){
            current = current->next;
            quickerCurrent = quickerCurrent->next->next;
        }
        auto middle = current; 
        //verify this with example: 0 1 2 3 and 0 1 2 3 4
        // TODO
        auto front = head;
        auto back = middle->next;
        middle -> next = nullptr;

        // reverse back
        {
            ListNode* prev = nullptr;
            auto current = back;
            while(current){
                auto next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            back = prev;// reversed
        }

        //merge
        {
            while(front && back){
                auto frontNext = front->next;
                auto backNext = back->next;
                front->next = back;
                back->next = frontNext;
                front = frontNext;
                back = backNext;
            }
        }

    }


    //  vector<> mapping index -> pointer, then reoder with 2 pointers
    // time: O(n), space O(n)
    void reorderList_vector(ListNode* head) {

        vector<ListNode*> nodes;
        ListNode * current = head;
        while(current){
            nodes.push_back(current);
            current = current->next;
        }

        int left = 0;
        int right = nodes.size()-1;

        while(left<right-1){
            auto next = nodes[left]->next;
            nodes[left]->next = nodes[right];
            nodes[right]->next = next;
            nodes[right-1]->next = nullptr;
            ++left;
            --right;
        }
        
    }
};
