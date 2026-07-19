#include "pch.h"
#include <iostream>
#include <stack>

/*
sort stack with antoher stack
*/

static void printStack(const std::stack<int> & s)
{
   for (std::stack<int> dump = s; !dump.empty(); dump.pop())
      std::cout << dump.top() << '\n';
   std::cout << "(" << s.size() << " elements)\n";
}

static int pop(std::stack<int> & s)
{
   int current = s.top();
   s.pop(); std::cout << "pop " << current << std::endl;
   return current;
}

static void sort_with_another_stack(std::stack<int> & s)
{
   std::stack<int> help;

   while (!s.empty())
   {
      int current = pop(s);

      while (!help.empty() && help.top() < current)//make sure bottom of help is that most big
      {
         s.push(pop(help));//elements smaller thans current will be push back to s
      }

      help.push(current);  //std::cout << "help push " << current << std::endl;
   }

   //all elements are in top-min-bottom-max order in help, now we just need to push them all back to original s
   while (!help.empty())
   {
      s.push(pop(help));
   }

}

static void sort(std::stack<int> & s)
{
   sort_with_another_stack(s);
}


int main()
{
   std::stack<int> stack;
   stack.push(4);
   stack.push(1);
   stack.push(3);
   stack.push(5);
   stack.push(2);

   printStack(stack);

   std::cout << "sort : \n";

   sort(stack);

   printStack(stack);

}
