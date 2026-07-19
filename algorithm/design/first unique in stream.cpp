#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>
#include <list>

using namespace std;

/*
First Unique Number in the data stream
Design a data strucutre with the following interfaces to find the first unique number in a datastream.
*/
class Stream {
    
public: 
    Stream():
    _uniquePos(),
    _order()
    {
    }

    void add(int num) 
    {
        auto it = _uniquePos.find(num);
        if(it != _uniquePos.end())
        {
            if(it->second != _order.end())
            {
                _order.erase(it->second);
                it->second = _order.end();
            }
        }
        else 
        {
            _order.push_back(num);
            _uniquePos[num] = (--_order.end());
        }
    }

    int* getFirstUnique() 
    {
        return _order.empty() ? nullptr : &_order.front();
    }
private:
    unordered_map<int, list<int>::iterator> _uniquePos;
    list<int> _order;
};

void print(int * num)
{

    cout<< (num!=nullptr ?to_string(*num) : "empty")<< endl; 
}

int main()
{
    Stream s;
    s.add(1);
    s.add(1);print(s.getFirstUnique());
    s.add(2);print(s.getFirstUnique());
    s.add(3);print(s.getFirstUnique());
    s.add(2);print(s.getFirstUnique());
    s.add(4);print(s.getFirstUnique());
    s.add(5);print(s.getFirstUnique());
    s.add(3);print(s.getFirstUnique());
    
    
}
