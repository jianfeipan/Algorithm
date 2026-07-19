/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param headA: the first list
     * @param headB: the second list
     * @return: a ListNode
     */
    ListNode * getIntersectionNode(ListNode * headA, ListNode * headB) {
        ListNode * intersectionBeginNode = nullptr;
        //idea: are they ordered : if ordered : we just need tow pointer to compare and move 
        ListNode * elementA = headA;
        ListNode * elementB = headB;
        while(elementA!=nullptr && elementB!=nullptr)
        {
            if(elementA->val == elementB->val)//question : are A, B 's intersection different nodes with same value or different nodes ?
            {
                return elementA;
            }
            else if(elementA->val > elementB->val)
            {
                elementB = elementB->next;
            }
            else
            {
                elementA = elementA->next;
            }
        }

        return intersectionBeginNode;
    }
};
