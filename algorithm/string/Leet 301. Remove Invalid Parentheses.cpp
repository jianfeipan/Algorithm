class Solution {
public:
    vector<string> removeInvalidParentheses(string s) 
    {
        return removeInvalidParentheses_recusive_backTrack_improved(s);
    }    
    
    //Idea: rcusively generate all possible validated strings see which are min 
    vector<string> removeInvalidParentheses_recusive_backTrack(string s) 
    {
        set<string> results;
        
        recusiveCollectResults(s, results, 0, "", 0, 0, 0);
        
        return vector<string>(results.begin(), results.end());
    }
    
    /*Idea to imprive :
        Problem : we try removing each and every possible parentheses
        Difficulty : there can be multiple valid expressions from a single invalid expression and we have to find all of them
        What we are sure: the final results are with min removal count and this is can be calculated before the recusive 
        
    
    
    */
    vector<string> removeInvalidParentheses_recusive_backTrack_improved(string s) 
    {
        int open = 0;
        int closeToBeRemoved = 0;
        
        for(char c : s)
        {
            if(c=='(')
            {
                ++open;
            }
            else if(c==')')
            {
                if(open>0) --open;
                else ++closeToBeRemoved;
            }
        }
        int openToBeRemoved = open;
        
        
        
        set<string> results;
        
        recusiveCollectResultsImprove(s, results, 0, "", 0, 0, 0, openToBeRemoved, closeToBeRemoved);
        
        return vector<string>(results.begin(), results.end());

        
        

    }

    
private:
    void recusiveCollectResults(const string & s,
                                set<string> & results,
                                int removeCount,
                                string currentSolution,
                                int currentIndex,
                                int openCount,
                                int closeCount)
    {
        //collect solutions if finish and valid : how to check if valid ? open == close
        if(currentIndex == s.size() &&  openCount == closeCount)
        {   
            //current solution is better    
            //cout<< currentSolution<< ": [" <<openCount<<", "<<closeCount<<"] removed "<< removeCount <<endl;
            if(removeCount<minRemoveCount)
            {
                results.clear();
                results.insert(currentSolution);
                minRemoveCount = removeCount;
            }
            else if(removeCount==minRemoveCount)
            {
                results.insert(currentSolution);
            }
        }    
        
        //generate solutions
        
        if(currentIndex<s.size())
        {
            if(s[currentIndex] != '(' && s[currentIndex] != ')')
            {
                recusiveCollectResults(s, results, removeCount, currentSolution + s[currentIndex], currentIndex+1, openCount, closeCount);
            }
            else
            {
                //branch 1 : remove current index
                recusiveCollectResults(s, results, removeCount + 1, currentSolution, currentIndex+1, openCount, closeCount);

                //branch 2 : keep current index
                if(s[currentIndex] == '(')
                {
                    recusiveCollectResults(s, results, removeCount, currentSolution+s[currentIndex], currentIndex+1, openCount+1, closeCount);
                }
                else if(s[currentIndex] == ')')
                {
                    if(openCount>closeCount)
                    {
                        recusiveCollectResults(s, results, removeCount, currentSolution+s[currentIndex], currentIndex+1, openCount, closeCount+1);
                    }
                }
            }
        }
        
    }
    
    void recusiveCollectResultsImprove(const string & s,
                                set<string> & results,
                                int removeCount,
                                string currentSolution,
                                int currentIndex,
                                int openCount,
                                int closeCount,
                                int openToBeRemoved,
                                int closeToBeRemoved
                                )
    {
        //cout<< currentSolution<< ": [" <<openCount<<", "<<closeCount<<"] removed "<< removeCount << "toRemove ["<<openToBeRemoved << ", "<< closeToBeRemoved<<"]"<<endl;

        //collect solutions if finish and valid : how to check if valid ? open == close
        if(currentIndex == s.size() &&  openCount == closeCount && openToBeRemoved == 0 &&closeToBeRemoved==0)
        {   
            //current solution is better    
            if(removeCount<minRemoveCount)
            {
                results.clear();
                results.insert(currentSolution);
                minRemoveCount = removeCount;
            }
            else if(removeCount==minRemoveCount)
            {
                results.insert(currentSolution);
            }
        }    
        
        //generate solutions
        
        if(currentIndex<s.size())
        {
            if(s[currentIndex] == '(' || s[currentIndex] == ')')
            {
                //branch 1 : remove current index
                if(s[currentIndex] == '(' && openToBeRemoved>0)
                {
                    recusiveCollectResultsImprove(s, results, removeCount + 1, currentSolution, currentIndex+1, openCount, closeCount, openToBeRemoved-1, closeToBeRemoved);
                }
                else if(s[currentIndex] == ')' && closeToBeRemoved>0)
                {
                    recusiveCollectResultsImprove(s, results, removeCount + 1, currentSolution, currentIndex+1, openCount, closeCount, openToBeRemoved, closeToBeRemoved-1);
                }

                //branch 2 : keep current index
                if(s[currentIndex] == '(')
                {
                    recusiveCollectResultsImprove(s, results, removeCount, currentSolution+s[currentIndex], currentIndex+1, openCount+1, closeCount,openToBeRemoved, closeToBeRemoved);
                }
                else if(s[currentIndex] == ')')
                {
                    if(openCount>closeCount)
                    {
                        recusiveCollectResultsImprove(s, results, removeCount, currentSolution+s[currentIndex], currentIndex+1, openCount, closeCount+1,openToBeRemoved, closeToBeRemoved);
                    }
                }
            }
            else
            {
                recusiveCollectResultsImprove(s, results, removeCount, currentSolution + s[currentIndex], currentIndex+1, openCount, closeCount, openToBeRemoved, closeToBeRemoved);
            }
        }
        
    }


private:
    int minRemoveCount = INT_MAX;
};
