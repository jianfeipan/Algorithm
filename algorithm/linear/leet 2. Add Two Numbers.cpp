/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode pointer1 = l1;
        ListNode pointer2 = l2;
        
        ListNode resultStartNode = new ListNode();
        ListNode resultPtr = resultStartNode;
        
        int digit = 1;
        int carry = 0;
        while(pointer1!=null || pointer2!=null || carry!=0){

            int number1 = pointer1==null ? 0 : pointer1.val;
            int number2 = pointer2==null ? 0 : pointer2.val;
            
            int temp =number1 + number2 + carry;
            resultPtr.val = temp%10;
            carry = temp/10;
            
            if(pointer1!=null)
                pointer1 = pointer1.next;
            if(pointer2!=null)
                pointer2 = pointer2.next;
            
            if(pointer1!=null || pointer2!=null || carry!=0)
            {
                resultPtr.next = new ListNode();
                resultPtr = resultPtr.next;
            }
        };
        
       
        return resultStartNode;
    }
    
    //another way to while
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        
        ListNode * start = new ListNode();
        auto * current = start;
        
        while(l1&&l2)
        {
            int result = l1->val+l2->val + carry;
            current->next = new ListNode(result % 10);
            carry = result / 10;
            
            l1=l1->next;l2=l2->next;current=current->next;
        }
        
        auto rest = l1 ? l1 : l2;
        
        while(rest)
        {
            int result = rest->val + carry;
            current->next = new ListNode(result % 10);
            carry = result / 10;
            
            current=current->next;rest=rest->next;
        }
        if(carry)
            current->next = new ListNode(carry);
        
        return start->next;
        
    }
    
    
}
