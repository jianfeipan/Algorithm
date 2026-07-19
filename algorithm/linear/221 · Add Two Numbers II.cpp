/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param l1: The first list.
     * @param l2: The second list.
     * @return: the sum list of l1 and l2.
     */
    ListNode * addLists2_small_int(ListNode * l1, ListNode * l2) {
        /*
        question : 
        negative numbers?
        val are all 0-9 num ?
        
        */
        /*
            idea1 : read to int and sum then write to linked list
                good: simple to handle the carry
                bad : overflow intmax

            idea2 : online the last element, from that element we start the add with carry
                good: no limit on int size
                bad : handle carry is complex, from back to front traversal is complex

        */
        if(!l1 || !l2) 
        {
            throw new std::invalid_argument("null input.");
            return nullptr;
        }
        int num1 = read(l1);
        int num2 = read(l2);

        return write(num1+num2);


    }

    //backforward traversal --> call stack-->too complex  :  heap stack managed the count and the rest well
    ListNode * addLists2(ListNode * l1, ListNode * l2) 
    {
        if(!l1 || !l2) 
        {
            throw new std::invalid_argument("null input.");
            return nullptr;
        }

        stack<int> s1;
        auto current1 = l1;
        while(current1)
        {
            s1.push(current1->val);
            current1 = current1->next;
        }

        stack<int> s2;
        auto current2 = l2;
        while(current2)
        {
            s2.push(current2->val);
            current2 = current2->next;
        }


        ListNode * current = nullptr;
        ListNode * previous = nullptr;
        int carry = 0;
        while(!s1.empty() || !s2.empty())
        {
            const int currentNum = pop(s1) + pop(s2) + carry;
            current = new ListNode(currentNum%10);
            carry = currentNum/10;
            current->next = previous; 
            previous= current;
        }

        if(carry>0)
        {
            auto next = new ListNode(carry);
            next->next = current;
            current = next;
        }
        return current;
    }

private:
    template<typename T>
    T pop(stack<T> & s)
    {
        if(s.empty()) return 0;
        else
        {
            auto result = s.top();
            s.pop();
            return result;

        }
    }


    int read(ListNode * node)
    {
        int result = 0;
        auto current = node;
        while(current)
        {
            if(result>INT_MAX/10)
                throw new std::invalid_argument("overflow INT_MAX is not supported.");
            result*=10;
            result+=current->val;
            current = current->next;
        }
        return result;
    }
    ListNode * write(int num)
    {   
        if(num==0) return new ListNode(0);

        //cout<<"for"<<num<<endl;
        ListNode * current = nullptr;
        ListNode * previous = nullptr;
        while(num)
        {
            //cout<<"push_back"<<num%10<<endl;

            current = new ListNode(num%10);
            current->next=previous;
            previous = current;
            num/=10;
        }
        return current;
    }
};
