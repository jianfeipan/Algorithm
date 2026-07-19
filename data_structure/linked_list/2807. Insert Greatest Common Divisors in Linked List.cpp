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


/*
2807. Insert Greatest Common Divisors in Linked List
Medium
78
3
Companies
Given the head of a linked list head, in which each node contains an integer value.

Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.

Return the linked list after insertion.

The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

 

Example 1:
Input: head = [18,6,10,3]
Output: [18,6,6,2,10,1,3]
Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
- We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
- We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
- We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
There are no more adjacent nodes, so we return the linked list.


Input: head = [7]
Output: [7]
Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes.
There are no pairs of adjacent nodes, so we return the initial linked list.
*/
class Solution {

private:
    int greatest_common_divisor(int left, int right)
    {
        int min = std::min(left, right);
        while(min>1)
        {
            if(left%min ==0 && right%min ==0) return min;
            --min;
        }
        return min;
    } 
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* current = head;
        ListNode* next = current->next;
        while(current && next)
        {
            auto * toInsert = new ListNode(greatest_common_divisor(current->val, next->val));
            current->next = toInsert;
            toInsert->next = next;

            current = next;
            next = current->next;
        }

        return head;
    }
};
