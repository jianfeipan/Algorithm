
/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
*/

class Solution {

/*
fact: 
    operator priority metters
    input number will be ints

idea:
    1 read all numbers and operators first
        --> a loop to call readNum and read operator
        --> need container for all numbers and operators. 
    2 then do the computation 
        --> process * and / frist, then + and -
        
    solution:
        can use stack: 



*/
public:
    int calculate_brut_force(string s) {
        
        vector<int> nums;
        vector<char> operators;

        int current = 0;
        for(char c:s)
        {
            if(c == '+' || 
            c == '-' ||
            c == '*' ||
            c == '/' )
            {
                nums.push_back(current);
                operators.push_back(c);
                current = 0;
            }
            else if(c!=' ')
            {
                current*=10;
                current += (c - '0');
            }
        }
        nums.push_back(current);//!!!!! LAST number

        {//* and /

            int currentResult = 1;
            int currentResultFromIndex = -1;
            
            for(int i = 0; i< operators.size(); ++ i)
            {
                if( operators[i] == '*' || operators[i] == '/')
                {
                    if(currentResultFromIndex == -1)
                    {
                        currentResultFromIndex = i;
                        currentResult = nums[i];
                    }
                    if( operators[i] == '*') currentResult*= nums[i+1];
                    else currentResult/= nums[i+1];
                }
                else
                {
                    if(currentResultFromIndex != -1)
                    {
                        for(int j = currentResultFromIndex; j<= i; ++j)
                        {
                            nums[j] = currentResult;
                            cout<< "set "<<j<<" to "<< currentResult<<endl;
                        }
                        currentResult = 1;
                        currentResultFromIndex = -1;
                    }
                }
            }
            //LAST num!!!!!
            if(currentResultFromIndex != -1)
            {
                for(int j = currentResultFromIndex; j< nums.size(); ++j)
                {
                    nums[j] = currentResult;
                    //cout<< "set "<<j<<" to "<< currentResult<<endl;
                }
            }
        }
        int res = nums[0];

        for(int i = 0; i< operators.size(); ++ i)
        {
            if( operators[i] == '+') 
            {
               res+=nums[i+1];
                
                
            }
            else if(operators[i] == '-')
            {
                res-=nums[i+1];
            }
        }
        return res;

    }

    int calculate(string s) 
    {
        int len = s.length();
        if (len == 0) return 0;

        stack<int> stack;
        int currentNumber = 0;
        char operation = '+';
        for (int i = 0; i < len; i++) {
            char currentChar = s[i];
            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == len - 1) {
                if (operation == '-') {
                    stack.push(-currentNumber);//- was treated as negative number
                } else if (operation == '+') {
                    stack.push(currentNumber);
                } else if (operation == '*') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop * currentNumber);
                } else if (operation == '/') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }

        //Only + left 
        int result = 0;
        while (stack.size() != 0) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};
