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
You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Example 2:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
Example 3:

Input: l1 = [0], l2 = [0]
Output: [0]



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
        //I need same length
        size_t len1 = count(l1);
        size_t len2 = count(l2);
        
        ListNode * filledL1 = l1;
        ListNode * filledL2 = l2;

        if(len1>len2) 
            filledL2 = fillWithZero(l2, len1 - len2);
        else if(len1 < len2)
            filledL1 = fillWithZero(l1, len2 - len1);
        
        return addSameLengthList(filledL1, filledL2);
        
    }
    
private:
    size_t count(ListNode * node)
    {
        size_t counter = 0;
        while(node)
        {
            node=node->next;
            ++counter;
        }
        
        return counter;
    }
    
    ListNode*  fillWithZero(ListNode* node, size_t count)
    {
        if(count==0) return node;
        return new ListNode(0, fillWithZero(node, count-1));//FIXME: memery leaking risk, this dilled nodes should be deleted
    }
    
    ListNode* addSameLengthList(ListNode* l1, ListNode* l2)
    {
        
        int carry = 0;
        auto sum = addSameLengthList(l1, l2, carry);
                
        return carry == 0 ? sum : new ListNode(carry, sum);//FIXME: to be deleted by caller
    }
    
    ListNode* addSameLengthList(ListNode* l1, ListNode* l2, int & carry)
    {
        if(!l1 && !l2) return nullptr;
        
        if(!l1 || !l2) throw invalid_argument("Input lists should have same length");
        
        int rightCarry = 0;
        auto rightNode =  addSameLengthList(l1->next, l2->next, rightCarry);
        
        const int sum = rightCarry + l1->val + l2->val;
        
        carry = sum/10;
        return new ListNode(sum%10, rightNode);//FIXME: to be deleted by caller
    }

    
};
