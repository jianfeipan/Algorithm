#include <string.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

/*
First question: Initially I was given a number that I should consider as terminating number. 
Given a continuous stream of numbers, 
write a function that returns the first unique number whenever terminating number is reached. 
Interviewer wanted an answer that was in O(1)
*/

class TopKVisited
{
 public:
    TopKVisited(size_t k):_k(k), _order(), _countAndIndex(){
        _order.reserve(_k);
    }
 
    void visit(int num)
    {
        if(_countAndIndex.count(num))
        {
            _countAndIndex[num].first++;
            adjustOrder(_countAndIndex[num].second, _countAndIndex[num].first, num);
        }
        else
        {
            if(_order.size() < _k)
            {
                _countAndIndex[num] = {1, _order.size()};
                _order.push_back(num);
            }
            else 
            {
                _countAndIndex[num] = {1, -1};
            }
        }
    }  
    
    void printTopK() const
    {
        for(auto num : _order) cout<<num<<", ";
        cout<< endl;
    }
    
private:
    void adjustOrder(int index, int count, int num)
    {
        if(index == -1)
        {
            if(_countAndIndex[_order.back()].first<count)
            {
                _countAndIndex[_order.back()].second = -1;
                _order.back() = num;
                index = _order.size()-1;
            }
        }
        
        if(index!=-1)
        {           
            while(index>0 && _countAndIndex[_order[index-1]].first < count)
            {
                auto temp = _order[index-1];
                _order[index-1] = _order[index];
                _order[index] = temp;
                --index;
            }
            _countAndIndex[num].second = index;
        }
    }
    
private:
    size_t _k;
    vector<int> _order;
    unordered_map<int, pair<int, int>> _countAndIndex;
};



int main(int argc, char *argv[])
{
    TopKVisited top3(3);
    
    top3.visit(1);top3.printTopK();
    top3.visit(1);top3.printTopK();
    top3.visit(2);top3.printTopK();
    top3.visit(3);top3.printTopK();
    top3.visit(2);top3.printTopK();
    top3.visit(3);top3.printTopK();
    top3.visit(2);top3.printTopK();
    top3.visit(3);top3.printTopK();
    top3.visit(4);top3.printTopK();
    top3.visit(4);top3.printTopK();
    top3.visit(4);top3.printTopK();
    top3.visit(5);top3.printTopK();
    top3.visit(4);top3.printTopK();
   

   return 0;
}
