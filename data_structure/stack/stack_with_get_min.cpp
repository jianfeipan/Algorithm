
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
class IGetMin
{
   virtual T getMin() = 0;
};

template<class T>
class StackWithGetMin : public IGetMin<T>
{

public:
   StackWithGetMin() {};

   T getMin() override
   {
      return _minStack.top();
   }

   void push(T t)
   {
      _data.push(t);
      if (_minStack.empty() || t < _minStack.top())
      {
         _minStack.push(t);//t is the min for curent
      }
      else
      {
         _minStack.push(_minStack.top());//push again the min because it's still the min
      }
   }

   void pop() 
   {
      _data.pop();
      _minStack.pop();
     
   }
   const std::stack<T> & getData()
   {
      return _data;
   }
   

private:
   std::stack<T> _data;
   std::stack<T> _minStack;
};


class MinStack {
private:
    stack<int> d_data;
    stack<int> d_min;
    
public:
    MinStack() {
    }
    
    void push(int val) {
        d_data.push(val);
        if(d_min.empty() || val<=d_min.top()){ // !! <= because we want to push the duplicate min value, when pop, we can pop the min value
            d_min.push(val);
        }
    }
    
    void pop() {

        if(d_data.top()==d_min.top()){
            d_min.pop();
        }
        d_data.pop();
        
    }
    
    int top() {
        return d_data.top();
    }
    
    int getMin() {
        return d_min.top();
    }
};



int main()
{
   StackWithGetMin<int> s;
   s.push(5);
   s.push(3);
   s.push(4);
   s.push(1);
   s.push(0);

   while (!s.getData().empty())
   {
      std::cout << "cuurent stack : " << std::endl;

      printStack(s.getData());

      std::cout << "cuurent min : " << s.getMin() << std::endl;

      s.pop();
   }


   return 0;

}
