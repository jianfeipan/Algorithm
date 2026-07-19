#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>
#include <stack>

using namespace std;

string removeUselessParentheses(const string & input)
{
    string formula = input;
    stack<int> left;
    
    bool shouldRemove = true;
    for(size_t i = 0; i<formula.size(); ++i)
    {
        if(formula[i] == '*' || formula[i] == '/')
        {
            shouldRemove = false;
        }
        else if(formula[i] == '+' || formula[i] == '-' )
        {
            shouldRemove = true;
        }
        else if(formula[i] == '(')
        {
            if(shouldRemove)
                left.push(i);
        }
        else if(formula[i] == ')')
        {
            if(!left.empty())
            {
                if(i<formula.size()-1 && (formula[i+1] == '*' || formula[i+1] == '/'))  left.pop();
                else
                {
                    formula[i] = ' ';
                    formula[left.top()] = ' ';
                    left.pop();
                }       
            }     
        }
    } 
    
    
    return formula;
}

int main()
{
    cout<< "cleaned :  " << removeUselessParentheses("((a+b)*c) + ((a+b) + c/(d + s))") <<endl;
    
    return 0;
}
