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
    ListNode* removeElements(ListNode* head, int val) 
    {
        ListNode root;
        root.next = head;
        auto * current = &root;
        
        while(current)
        {
            if(current->next && current->next->val == val) 
                current->next = current->next->next;
            else
                current = current->next;
        }
        
        return root.next;
    }
};
