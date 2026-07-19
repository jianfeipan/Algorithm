#include <string.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <list>
#include <unordered_map>
using namespace std;

/*
First question: Initially I was given a number that I should consider as terminating number. 
Given a continuous stream of numbers, 
write a function that returns the first unique number whenever terminating number is reached. 
Interviewer wanted an answer that was in O(1)
*/

class UniqueNumberInStream
{
 public:
    void push(int num)
    {
        if(_unique.count(num))
        {
            if(_unique[num] != _order.end())
            {
                _order.erase(_unique[num]);
                _unique[num] = _order.end();
            }
        }
        else 
        {
            _order.insert(_order.begin(), num);
            _unique[num] = _order.begin();
        }
    }   
    
    int getFirstUnique() const
    {
        if(!_order.empty()) return _order.back();
        return -1;
    }
    
private:
    unordered_map<int, list<int>::iterator> _unique;
    list<int> _order;
};

int main(int argc, char *argv[])
{
    UniqueNumberInStream unique;
    
    unique.push(1);cout<<unique.getFirstUnique()<<endl;
    unique.push(1);cout<<unique.getFirstUnique()<<endl;
    unique.push(2);cout<<unique.getFirstUnique()<<endl;
    unique.push(3);cout<<unique.getFirstUnique()<<endl;
    unique.push(3);cout<<unique.getFirstUnique()<<endl;
    unique.push(4);cout<<unique.getFirstUnique()<<endl;
    unique.push(2);cout<<unique.getFirstUnique()<<endl;
    unique.push(5);cout<<unique.getFirstUnique()<<endl;
    unique.push(4);cout<<unique.getFirstUnique()<<endl;
    
   
   return 0;
}
