/*
You are given two non-empty linked lists, l1 and l2, where each represents a non-negative integer.

The digits are stored in reverse order, e.g. the number 321 is represented as 1 -> 2 -> 3 -> in the linked list.

Each of the nodes contains a single digit. You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Return the sum of the two numbers as a linked list.

Input: l1 = [1,2,3], l2 = [4,5,6]

Output: [5,7,9]

Explanation: 321 + 654 = 975.
Example 2:

Input: l1 = [9], l2 = [9]

Output: [8,1]
Constraints:

1 <= l1.length, l2.length <= 100.
0 <= Node.val <= 9



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
public:
    /*
    facts:
        1.linked list is from smaller digital
        2.non-negative numbers
    idea: 
        two pointers
        sum nodes, if >10, use a flag to note there is a 10
        then next, util both list  null 

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
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode before_first;
        auto prev = &before_first;
        auto cur1 = l1;
        auto cur2 = l2;
        while(cur1 && cur2) {
            int sum = cur1->val + cur2->val + carry;
            carry = sum/10;
            prev->next = new ListNode(sum%10);
            prev = prev->next;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        auto rest = cur1 ? cur1 : cur2;
        while( rest ) {
            int sum = rest->val + carry;
            carry = sum/10;
            prev->next = new ListNode(sum%10);
            prev = prev->next;
            rest = rest->next;
        }

        if(carry){
            prev->next = new ListNode(carry);
        }

        return before_first.next;
    }
};

