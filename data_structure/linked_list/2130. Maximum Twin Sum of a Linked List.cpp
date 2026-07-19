/**
In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.

 

Example 1:


Input: head = [5,4,2,1]
Output: 6
Explanation:
Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
There are no other nodes with twins in the linked list.
Thus, the maximum twin sum of the linked list is 6. 
Example 2:


Input: head = [4,2,2,3]
Output: 7
Explanation:
The nodes with twins present in this linked list are:
- Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
- Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
Thus, the maximum twin sum of the linked list is max(7, 4) = 7. 




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
/*
fact:
    1 singly linked list
    2 sum, max
idea:
    1 double pointer: slow and fast--> to fin the middle one
    2 a container to store the fist 1/2 and the left we sum backward and the same iteration, we can do a compare

*/
public:
    int pairSum_extra_container(ListNode* head) {
        
        int max = 0;

        ListNode * slow = head;
        ListNode * fast = head;

        vector<int> firstHalf;

        while(slow && fast)
        {
            firstHalf.push_back(slow->val);
            slow=slow->next;
            fast=fast->next? fast->next->next : nullptr;
        }

        ListNode * secondHalf= slow;

        for(auto rit = firstHalf.rbegin();  rit!=firstHalf.rend(); ++rit, slow=slow->next)
        {
            max = std::max(max, *rit+slow->val);
        }

        return max;
    }   

    int pairSum(ListNode* head) {//We can change the intput :( to save memory
        
        int max = 0;

        ListNode * slow = head;
        ListNode * fast = head;

        ListNode * prev = nullptr;

        while(slow && fast) //count to middle and reverse the first half
        {

            fast= (fast->next? fast->next->next : nullptr);//Move fast before slow reversing the first half

            ListNode * slowNext = slow->next;
            slow->next = prev;
            prev = slow;
            slow=slowNext;

        }

        while(slow && prev)
        {
            max = std::max(max, slow->val+prev->val);
            slow = slow->next;
            prev = prev->next;
        }

        return max;
    }   
};
