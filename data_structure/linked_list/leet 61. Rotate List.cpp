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
    ListNode* rotateRight(ListNode* head, int k) 
    {
        if(!head) return nullptr;
        
        if(k == 0) return head;
        
        size_t size = count(head);
        
        if(size==1) return head;
        
        int realRoteNumber = k % size;    
        
        if(realRoteNumber==0) return head;
        
        realRoteNumber = size - realRoteNumber;//pay attention to the rotatiion direction!!! we do size-k to change the direction
        
        auto * current = head;
        while(--realRoteNumber>0)
        {
            current= current->next;
        }
        
        auto rotated = current->next;
        current->next = nullptr;
        
        auto * last = rotated;
        while(last->next)
        {
            last= last->next;
        }
        last->next = head;
        
        return rotated;
    }
private:
    size_t count(ListNode* head)
    {
        size_t count = 0;
        while(head)
        {
            head = head->next;
            ++count;
        }
        return count;
    }
};
