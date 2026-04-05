/*
You are given the head of a singly linked list head and a positive integer k.

You must reverse the first k nodes in the linked list, and then reverse the next k nodes, and so on. If there are fewer than k nodes left, leave the nodes as they are.

Return the modified list after reversing the nodes in each group of k.

You are only allowed to modify the nodes' next pointers, not the values of the nodes.

Example 1:



Input: head = [1,2,3,4,5,6], k = 3

Output: [3,2,1,6,5,4]
Example 2:



Input: head = [1,2,3,4,5], k = 3

Output: [3,2,1,4,5]
Constraints:

The length of the linked list is n.
1 <= k <= n <= 100
0 <= Node.val <= 100

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
private:
    void reverse(ListNode* head, ListNode* tail){
        if(head == tail) return;

        auto prev = head;
        auto current = prev->next;
        while(current!=tail){
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        tail->next = prev; // last one reverse
        head->next = nullptr;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode beforeFirst;
        auto* reversedTail = &beforeFirst;

        auto* groupHead = head;
        ListNode* groupTail = nullptr;
        int n = 0;

        auto* current = head;
        while(current){
            auto* next = current->next;
            // 1->2->3->4->5->6
            ++n;
            if(n == k){
                groupTail = current;
                reverse(groupHead, groupTail);

                reversedTail->next = groupTail;
                reversedTail = groupHead;
                
                n=0;
                groupHead = next;
            } 
            // group head, group tail
            // gh    gt       gh
            // 1<-2<-3 next = 4->5->6
            current = next;
        }
        
        reversedTail->next = groupHead;
        return beforeFirst.next;
    }
};
