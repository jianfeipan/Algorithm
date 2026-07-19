class Solution {
public:
    int findMinStep(string board, string hand) 
    {
        unordered_map<char, int> seeds;
        for(auto c : hand) ++seeds[c];
        
        return findMinStep_dp(board+"#", seeds);
    }

    
    
    int findMinStep_dp(string board, unordered_map<char, int> hand) 
    {
        board = clear(board);
        cout<<board<<endl;
        
        if(board=="#") return 0;
        
        int minuNumber = INT_MAX;
        for (int i = 0, j = 0 ; j < board.size(); ++j) 
        {
            const char current = board[i];
            if (board[j] == current) continue;
            
            const int need = 3 - (j - i);//balls need to remove current consecutive balls.
            if (hand[current] >= need) 
            {
                hand[current] -= need;
                const int next = findMinStep_dp(board.substr(0, i) + board.substr(j), hand);
                if(next!=-1)
                    minuNumber = min(minuNumber, need + next);
                
                hand[current] += need;//track back
            }
            i = j;
        }
        
        return minuNumber < INT_MAX ? minuNumber : -1;
    }
    
    
private:
    string clear(const string & toClear)
    {
        for(size_t i = 0, j = 0; i<toClear.size(); ++j)
        {
           if(toClear[i] == toClear[j]) continue; 
           if(j - i >= 3 ) return clear(toClear.substr(0, i) + toClear.substr(j));
           else i = j;
        }
        return toClear;
    }
};
