#include <string.h>
#include <stdio.h>
#include <iostream>
#include <memory>
using namespace std;

/*
Write a linked list class along with append function(add a node at the end) and destructor function.
*/
template<class T>
class  Node
{
public:
    Node(const T & val):_val(val){}
    
    T _val;
    unique_ptr<Node<T>> _next;
};

template<class T>
class MyLinkedList
{
public:
    MyLinkedList():_root(), _tail(nullptr)
    {
    }
    
    ~MyLinkedList()
    {
    }
    
    void append(const T & element)
    {
        if(_tail == nullptr)
        {
            //_root.reset(new Node<T>(element));
            _root = make_unique<Node<T>>(element);
            _tail = _root.get();
        }
        else 
        {
            Node<T>* node = new Node<T>(element);
            _tail->_next.reset(node);   
            _tail = _tail->_next.get(); 
        }
    }
    
    void print() const
    {
        Node<T> * current = _root.get();
        while(current)
        {
            cout<<current->_val<<"->";
            current = current->_next.get();
        }
        
    }
    
private:
    unique_ptr<Node<T>> _root;
    Node<T> * _tail;
};



int main(int argc, char *argv[])
{
    MyLinkedList<int> l;
    l.append(1);
    l.append(2);
    l.append(3);
    l.append(4);
    l.print();  
     return 0;
}
