/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
using namespace std;


int fibonacci_recusive(size_t i)
{
    if(i<=1)
        return 1;
    else
        return fibonacci_recusive(i-1) + fibonacci_recusive(i-2);
}
//time : O(2^N)
//space: O(logN)

int fibonacci_with_memory(size_t i)
{
    vector<int> memory(i+1, -1);
    memory[0] = memory[1] = 1;
    
    if(memory[i] != -1)
    {
        return memory[i];
    }
    else
    {
        memory[i] = fibonacci_with_memory(i-1) + fibonacci_with_memory(i-2);
        return memory[i]; 
    }
}
//time : O(N)
//space : O(N)

int fibonacci_tabulation(size_t i)
{
    int result = 1;
    int privious = 1;
    for(int j = 2; j<=i; ++j)
    {
        int current = result;
        result+= privious;
        privious = current;
    }
    return result;
}
//time : O(N)
//space : O(1)


int main()
{
    for(int i = 0; i<=10; ++i)
        cout<<"fibonacci(" << i << ") = "<< fibonacci_tabulation(i)<<endl;

    return 0;
}
