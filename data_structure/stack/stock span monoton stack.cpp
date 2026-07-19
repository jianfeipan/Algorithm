

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*
The stock span problem is a financial problem where we have a series of n daily price quotes for a stock and we need to calculate span of stock’s price for all n days. 
The span Si of the stock’s price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the current day is less than its price on the given day. 
For example, if an array of 7 days prices is given as {100, 80, 60, 70, 60, 75, 85}, then the span values for corresponding 7 days are {1, 1, 1, 2, 1, 4, 6} 
*/

vector<int> stockSpans_brute_force(const vector<int>& prices) //O(N^2)
{
    /*
    brute force
    */
    vector<int> spans;spans.reserve(prices.size());
    
    for(size_t i = 0; i<prices.size(); ++i)
    {
        size_t count = 1;
        for(int back = i-1; back>=0; --back)
        {
            if(prices[back]<prices[i]) count++;
            else break;
        }
        spans.push_back(count);
    }
    return spans;
}

vector<int> stockSpans_monoton_stack(const vector<int>& prices) //O(N)  S: O(N)
{
    /*
    the smaller ones are already counted by the taller ones
    use a stack only take taller ones on the left, then if a taller comes,
    pop them, and add theirs spans becauses smaller ones definitly smaller than current
    */
    vector<int> spans;spans.reserve(prices.size());
    spans.push_back(1);
    
    stack<size_t> left;
    
    for(size_t i = 1; i<prices.size(); ++i)
    {
        size_t currentSpan = 1;
        while(!left.empty() && prices[left.top()]< prices[i])
        {
            currentSpan+=spans[left.top()];left.pop();
        }
        left.push(i);
        spans.push_back(currentSpan);
    }
    return spans;
}

vector<int> stockSpans_monoton_stack2(const vector<int>& prices) //O(N)  S: O(N)
{
    /*
   same idea of monoton stack, but here we don't use the number from spans, we can get the number directly from the index!!!!
    */
    vector<int> spans;spans.reserve(prices.size());   
    stack<size_t> left;
    
    for(size_t i = 0; i<prices.size(); ++i)
    {
        while(!left.empty() && prices[left.top()]< prices[i]) left.pop();
        spans.push_back(left.empty() ? i + 1 : i - left.top());//----> i - left is alreay the number of days
        left.push(i);
    }
    return spans;
}

vector<int> stockSpans(const vector<int>& prices) 
{
    return stockSpans_monoton_stack2(prices);
}


int main(int argc, char *argv[])
{
   auto subsequence = stockSpans({100, 80, 60, 70, 60, 75, 85});
   
   for(auto num : subsequence) cout<< num<<", ";
   cout<<endl;
   return 0;
}
