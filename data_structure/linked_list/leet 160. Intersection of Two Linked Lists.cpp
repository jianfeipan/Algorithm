/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        return getIntersectionNode_use_differece(headA, headB);
    }
    
    ListNode *getIntersectionNode_use_differece(ListNode *headA, ListNode *headB) 
    {
        auto lenA = getLen(headA);
        auto lenB = getLen(headB);
        
        ListNode * longList = nullptr;  
        ListNode * shortList = nullptr;

        size_t difference = 0;
        if(lenA >= lenB)
        {
            longList = headA;
            shortList = headB;
            difference = lenA - lenB;
        }
        else
        {
            longList = headB;
            shortList = headA;
            difference = lenB - lenA;            
        }
        
        
        while(difference && longList)
        {
            cout<<difference<<endl;
            longList=longList->next;
            --difference;
        }
        

        
        while(longList && shortList)
        {
            
            if(longList == shortList) return longList;
            
            longList=longList->next;
            shortList=shortList->next;
            
        }
        
        return nullptr;
        
    }

    ListNode *getIntersectionNode_brute_force(ListNode *headA, ListNode *headB) 
    {
        auto pa = headA;
        while(pa)
        {
            auto pb = headB;
            while(pb)
            {
                if(pa == pb) return pa;
                
                pb = pb->next;
            }
            pa = pa->next;
        }
        return nullptr;
    }
    
private:
    size_t getLen(ListNode * head)
    {
        size_t len = 0;
        while(head)
        {
            ++len;
            head=head->next;
        }
        return len;
        
    }
};
