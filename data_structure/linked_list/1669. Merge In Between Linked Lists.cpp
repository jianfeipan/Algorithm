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
 1669. Merge In Between Linked Lists
You are  given two linked lists: list1 and list2 of sizes n and m respectively.

Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

The blue edges and nodes in the following figure indicate the result:


Build the result list and return its head.

 

Example 1:


Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [10,1,13,1000000,1000001,1000002,5]
Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
Example 2:


Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
Explanation: The blue edges and nodes in the above figure indicate the result.
 

Constraints:

3 <= list1.length <= 104
1 <= a <= b < list1.length - 1
1 <= list2.length <= 104
 
 
 */
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        if(!list1) return list1;


        ListNode* list2Start = list2;
        ListNode* list2End = list2;
        while(list2){
            list2End = list2;
            list2 = list2->next;
        }

        ListNode* current = list1;
        while(a-1>0){
            //ASSERT_TRUE(current)
            current = current->next;
            --a;
            --b;
        }

        // std::cout<<"a: "<< current->val << std::endl;

        ListNode* orginal = current->next;
        current-> next = list2Start;
        
        current = orginal;


        while(b-1>0){
            //ASSERT_TRUE(current)
            current = current->next;
            --b;
        }

        // std::cout<<"b: "<< current->val << std::endl;

        list2End->next = current->next;

        //Destroy orginal 

        return list1;
    }
};
