class Solution {
  /*
  A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.


"()"
"())"
"((("
  */
public:
  int minAddToMakeValid(string s) {
      return minAddToMakeValid_counter(s);
  }
  
  int minAddToMakeValid_counter(string s) {
        int minAdd = 0;
        int opens = 0;
        
        for(char c : s)
        {
            if(c==')')
                if(opens==0) ++minAdd;
                else --opens;
            else 
                ++opens;
        }

        
        return minAdd + opens;
    }
    int minAddToMakeValid_stack(string s) {
        int minAdd = 0;
        stack<char> opens;
        
        for(char c : s)
        {
            if(c==')')
                if(opens.empty()) ++minAdd;
                else opens.pop();
            else 
                opens.push(c);
        }
        
        while(!opens.empty())
        {
            ++minAdd;
            opens.pop();
        }
        
        return minAdd;
    }
};
