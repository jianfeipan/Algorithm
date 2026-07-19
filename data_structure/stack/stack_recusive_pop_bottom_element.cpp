#include <iostream>
#include <stack>


/*

use recusive call to invers a stack

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

static int popBottomElement(std::stack<int> & s) //
{
   /*
   pop the bottom element

   4
   3
   2
   1

   pop 4
      pop 3
         pop 2
            pop 1



            return 1
         push 2
         return 1
      push 3
      return 1
   push 4
   return 1
   */
   int current = pop(s);

   if(s.empty())
   {
      return current;
   }
   else
   {
      int last = popBottomElement(s);
      s.push(current); std::cout << "push " << current<<std::endl;
      return last;
   }
}


static void inverseStack(std::stack<int> & s)
{
   if (!s.empty())
   {
      int i = popBottomElement(s);
      inverseStack(s);
      s.push(i);
   }
}

int main()
{
   std::stack<int> stack;
   stack.push(1);
   stack.push(2);
   stack.push(3);
   stack.push(4);

   printStack(stack);
   
   std::cout << "inverse : \n"; 

   inverseStack(stack);
   
   printStack(stack);

}
