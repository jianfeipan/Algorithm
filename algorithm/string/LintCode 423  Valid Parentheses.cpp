class Solution {
public:
    /**
     * @param s: A string
     * @return: whether the string is a valid parentheses
     */
    bool isValidParentheses(string &s) {
        //stack
        stack<char> opened;


        for(char c : s)
        {
            switch (c)
            {
                case '(':
                case '[':
                case '{':
                {
                    opened.push(c);
                    break;
                }
                case ')':
                case ']':
                case '}':
                {
                    if(opened.empty() || !isPair(opened.top(), c))
                        return false;
                    else
                        opened.pop();
                    break;
                }
            }
        }

        return opened.empty();
    }
private:
    bool isPair(char left, char right)
    {
         switch (left)
            {
                case '(':
                    return right == ')';
                case '[':
                    return right == ']';
                case '{':
                    return right == '}';
                default:
                    throw new std::invalid_argument("bad input");
            }
            return false;
    }
};
