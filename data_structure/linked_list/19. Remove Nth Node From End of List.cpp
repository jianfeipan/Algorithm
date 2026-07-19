/*
You are given the beginning of a linked list head, and an integer n.

Remove the nth node from the end of the list and return the beginning of the list.

Example 1:

Input: head = [1,2,3,4], n = 2

Output: [1,2,4]
Example 2:

Input: head = [5], n = 1

Output: []
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
    //two pointers one pass
    // 1 2 3 4 5, ..., n = 2
    // r
    //   r          n =2 --n
    //     r          =1 --n
    //       r        =0 --n
    // l     r         loop until r = nullptr
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto r = head;
        while(n>0){
            r=r->next;
            --n;
        }
        ListNode beforeFirst;
        beforeFirst.next = head;
        auto prev = &beforeFirst;

        auto l = head;
        while(r){
            prev = l;
            l = l->next;
            r = r->next;
        }
        prev->next = l->next;
        return beforeFirst.next;
    }

    // BF: two pass: one to find total size, then remove size - n' element
    // O(n) 
    ListNode* removeNthFromEnd_twopass(ListNode* head, int n) {
        auto current = head;
        int total = 0;
        while(current){
            ++total;
            current = current->next;
        }
        // 1 2 3 4 , 4 elements, remove the 2nd from last one, will be the 3rd from beginning
        int count = 0;
        // 0 1 2 
        const int target = total-n;
        current = head;
        ListNode beforeFirst;
        beforeFirst.next = head;
        ListNode* prev = &beforeFirst;
        while(count<target){
            prev = current;
            current=current->next;
            ++count;
        }

        prev->next = current->next;
        return beforeFirst.next;
    }
};
