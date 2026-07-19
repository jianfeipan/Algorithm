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
    ListNode* reverseList(ListNode* head) {
        
        if(!head || !head->next) return head;
        
        ListNode* previous = nullptr;
        auto current = head;
        
        while(current)
        {
            auto next = current->next;//note next somewhere before change it
            current->next = previous;
            
            previous = current;
            current = next;
        }
        
        
        return previous;
    }
};
