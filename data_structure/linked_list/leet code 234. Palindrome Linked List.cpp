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
    bool isPalindrome(ListNode* head) 
    {
        return isPalindrome_toVector(head);
    
    }
    bool isPalindrome_toVector(ListNode* head)
    {
        vector<int> nums;
        while(head)
        {
            nums.push_back(head->val);
            head=head->next;
        }
        
        for(int i = 0; i < nums.size()/2; ++i)
        {
            if(nums[i] != nums[nums.size() -1 -i])
                return false;
        }
        return true;
    }

    bool isPalindrome_inplace(ListNode* head) 
    {
        //Idea count, reverse the first N/2 and compare from N/2 to 0  and to N-1
        //in LINEDLIST, we have a every tricky way to find middle point: one slow pointer increment +1 an d fast pointer increment +2: when fast comes to end, slow is on th e middle
        
        ListNode *pre = NULL,*fast=head,*slow=head;
        
        while(fast && fast->next)
        {
            fast=fast->next->next;
            ListNode *tmp=slow;
            slow=slow->next;
            tmp->next=pre;
            pre=tmp;
        }
        if(fast!=NULL)
        {
            slow=slow->next;
        }
       return isSameList(pre,slow);
    }
    
    
private:
    bool isSameList(ListNode *node0,ListNode *node1)
    {
        while(node0 &&node1)
        {
            if(node0->val!=node1->val)return false;
            node0=node0->next;
            node1=node1->next;
        }
        return true;
    }


       
};
