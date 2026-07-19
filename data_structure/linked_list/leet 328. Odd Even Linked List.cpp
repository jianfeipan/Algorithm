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
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) return head;
        
        ListNode* oddStart = head;
        ListNode* evenStart = head->next;
        
        auto * odd = oddStart;
        auto * even = evenStart;
        auto * current = even->next;
        while(current)
        {
            odd->next = current;
            even->next = current->next;
            
            odd = odd->next;
            even = even->next;
            
            current = even ? even->next : nullptr;
        }
        
        odd->next = evenStart;
        
        return oddStart;
        
    }
};
