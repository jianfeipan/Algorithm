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
 
 2487. Remove Nodes From Linked List
Medium
Topics
Companies
Hint
You are given the head of a linked list.

Remove every node which has a node with a greater value anywhere to the right side of it.

Return the head of the modified linked list.

 

Example 1:


Input: head = [5,2,13,3,8]
Output: [13,8]
Explanation: The nodes that should be removed are 5, 2 and 3.
- Node 13 is to the right of node 5.
- Node 13 is to the right of node 2.
- Node 8 is to the right of node 3.
Example 2:

Input: head = [1,1,1,1]
Output: [1,1,1,1]
Explanation: Every node has value 1, so no nodes are removed.
 

Constraints:

The number of the nodes in the given list is in the range [1, 105].
1 <= Node.val <= 105
 
 
 */



/*
Fact: 
    1 linked list, what we got is the head
    2 remove node if any larger number in the "nexts" nodes

idea:
    1 recuresive: 
            maxValue = 0;
            (afterDelete, maxValue)  = remove(head)
            if head.val > maxValue
                head->next = afterDeleted



*/
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        return  removeNodes_rec(head);
    }

private:
    ListNode* removeNodes_rec(ListNode* head) {
        //Boundary 
        if(!head){
            return head;
        }
        
        int nextMaxValue = 0; 
        head ->next = removeNodes_rec(head->next);

        if(head->next && (head->val) < (head->next->val)){
            return head->next;//remove
        }
        else{
            return head;//keep
        }
    }
};
