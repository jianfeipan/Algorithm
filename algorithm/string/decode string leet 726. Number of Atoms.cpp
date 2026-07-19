class Solution {
public:
    string countOfAtoms(string formula) 
    {
        map<string, size_t> atoms = count(formula);
        return printCounts(atoms);
    }
    
private:
    map<string, size_t> count(const string & formula)
    {
        int from = 0;
        string formulaWithoutParethese = decodeParathese(formula, from);
        return count_without_parenthese(formulaWithoutParethese);
    }
    
    string decodeParathese(const string & formula, int & i)
    {
        string decoded;
        
        string currentExpression;
        while(i<formula.size())
        {
            const char c = formula[i];
            if(c == '(')
            {
                ++i;
                currentExpression+=decodeParathese(formula, i);
            }
            else if(c==')')
            {
                ++i;
                const int count = readNum(formula, i);
                if(count>0)
                    for(int j = 0; j<count;++j) decoded+=currentExpression;
                else
                    decoded+=currentExpression;
                currentExpression.clear();
                
                return decoded;
            }
            else
            {
                currentExpression+=c;
                ++i;
            }
        }
        
        return decoded + currentExpression;
    }
    
    
    map<string, size_t> count_without_parenthese(const string & formula)
    {
        map<string, size_t> counts;
        
        string currentAtom;
        int i = 0;
        while(i<formula.size())
        {
            const char c = formula[i];
            if(isdigit(c))
            {
                counts[currentAtom] +=readNum(formula, i); 
                currentAtom.clear();
            }
            else 
            {
                if(isupper(c))
                {
                    if(!currentAtom.empty())
                    {
                        counts[currentAtom] +=1;
                        currentAtom.clear();
                    }
                }
                currentAtom+=c;
                ++i;
            }
        }
        counts[currentAtom] +=1;
        return counts;
    }
    
    int readNum(const string & formula, int & i)
    {
        int count = 0;
        while(isdigit(formula[i]) && i<formula.size())
        {
            count*=10;
            count += formula[i]-'0';
            ++i;
        }
        return count;
    }
    
    string printCounts(const map<string, size_t> & atoms)
    {
        string output;
        
        for(const auto & [atom, count] : atoms)
        {
            output+=atom;
            if(count>1) output+=to_string(count);
        }
        return output;
    }
};
