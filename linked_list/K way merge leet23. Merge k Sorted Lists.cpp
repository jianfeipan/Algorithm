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
 ideas:
    1 4 5
    1 3 4
    2 6

    compare first from all list, take the smallers, move that pointer, then next round, until all poitners to the end
    -> minHeap: the top is smallest, size : number of lists log(k)
 
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        auto greater = [] (auto left, auto right) {
            return left->val > right->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(greater)> minHeap(greater);
        for(auto head : lists) minHeap.push(head);
        
        ListNode before_first;
        auto prev = &before_first;
        while( !minHeap.empty() ) {
            // pick the smallest
            auto min_head = minHeap.top(); minHeap.pop();
            if(min_head->next) minHeap.push(min_head->next);
            
            prev->next = min_head;
            prev = prev->next;
        }
        return before_first.next;
    }
};

