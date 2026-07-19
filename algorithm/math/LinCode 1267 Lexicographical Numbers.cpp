class Solution {
public:
    /**
     * @param n: an integer
     * @return: 1 - n in lexicographical order
     */
    vector<int> lexicalOrder(int n) {
        vector<int> lexical;
        lexical.reserve(n);
        pushValue(lexical, 0, n);
        return lexical;
    }
public:
    void pushValue(vector<int> & lexical, int current, int n)
    {
        current*=10;
        for(int i = 0; i<=9; ++i)
        {
            int newNum = current+i;
            if(newNum>0)
            {
                if(newNum <= n)
                { 
                    lexical.push_back(newNum);
                    pushValue(lexical, newNum, n);
                }
                else
                    break;
            }
        }
    }
};
