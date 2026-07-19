#include "pch.h"
#include <iostream>
#include <stack>



static void printStack(const std::stack<int> & s)
{
   for (std::stack<int> dump = s; !dump.empty(); dump.pop())
      std::cout << dump.top() << '\n';
   std::cout << "(" << s.size() << " elements)\n";
}

static int pop(std::stack<int> & s)
{
   int current = s.top();
   s.pop(); //std::cout << "pop " << current << std::endl;
   return current;
}

template<class T>
class IQueue
{
   virtual void add(T t) = 0;
   virtual void poll() = 0;
   virtual T peek() = 0;
   virtual bool empty() = 0;
};

template<class T>
class TwoStackQueue : public IQueue<T>
{

public:
   TwoStackQueue() {};

   virtual void add(T t) override final
   {
      while (!_out.empty())
      {
         _in.push(pop(_out));
      }
      _in.push(t);
   }
   virtual void poll() override final
   {
      while (!_in.empty())
      {
         _out.push(pop(_in));
      }
      _out.pop();
   }
   virtual T peek() override final
   {
      while (!_in.empty())
      {
         _out.push(pop(_in));
      }
      return _out.top();
   }

   virtual bool empty() override final
   {
      return _in.empty() && _out.empty();
   }


private:
   std::stack<T> _in;
   std::stack<T> _out;


};


int main()
{
   TwoStackQueue<int> myQueue;
   myQueue.add(1);
   myQueue.add(2);
   myQueue.add(3);
   myQueue.add(4);

   while (!myQueue.empty())
   {
      std::cout << myQueue.peek() << std::endl;
      myQueue.poll();
   }


   return 0;

}
