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
     * @param head: a ListNode
     * @return: a ListNode
     */
    ListNode * swapPairs(ListNode * head) {
        
       ListNode * previous = head;
       
       while(previous)
       {
           ListNode * current = previous->next;
           if(!current) break;

           int temp = current->val;
           current->val = previous->val;
           previous->val = temp;

           previous = current->next;
       } 

       return head;
    }
};
