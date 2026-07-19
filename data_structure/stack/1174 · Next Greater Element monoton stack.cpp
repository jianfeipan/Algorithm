class Solution {
public:
    /**
     * @param n: an integer
     * @return: the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n
     */
    int nextGreaterElement(int n) {
        if(n/10 == 0) return 0;
        /*
            1174 · Next Greater Element monoton stack
        
            idea: for example: 132 --> i need to swap 1 and 2, go get 213
            go from right to left, with a monoton stack
                    
             最后一个位置开始，找到下降点，下降点之前的无需改动。
                然后 这个点右边按降序排列，找到一个比当前点大的最小值，然后交换
                还是把int 转成vector 比较好操作
        
        */
        
        stack<int> rightSide;

        auto number = n;
        int current = -1;

        bool findDecedingValue  =false;
        while(number)//construct monoton stack : till the first decrising number
        {
            current = number%10;
            number/=10;
            if(rightSide.empty())
                rightSide.push(current);
            else
            {
                if(current>=rightSide.top())
                {
                    rightSide.push(current);
                }
                else
                {
                    findDecedingValue = true;
                    break;
                }
            }            
        }
        //current is the first decrising number
        //then we need to find the smallest in stack which is bigger then current

        if(!findDecedingValue )
            return -1;

        //get the smallest value in the stack which bigger than current
        int factor = 1;
        int rightSideNumber = 0;

        int top = rightSide.top();rightSide.pop();
        while(!rightSide.empty() && current<rightSide.top())
        {
            rightSideNumber+=top * factor;
            factor*=10;
            top = rightSide.top();rightSide.pop();
        }

        //here top is the smallest biger than current, top will replace current, and current will bw in stack
        rightSide.push(current);
        while(!rightSide.empty())
        {
            rightSideNumber+=rightSide.top() * factor;
            rightSide.pop();
            factor*=10;
        }

        //cout<<number<<" - "<<current<<"+"<<top<<endl;
        //change current to top then with the factor, we combine all together
        return (number*10 + top) * factor + rightSideNumber;
    }

};
