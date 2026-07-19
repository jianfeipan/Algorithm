class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //BFS try to find the path
        queue<string> level;
        size_t depth = 1;
        
        unordered_set<string> notVisited(wordList.begin(), wordList.end());
        level.push(beginWord);
        notVisited.erase(beginWord);
        
        while(!level.empty())
        {
            int size = level.size();
            
            while(size-->0)
            {
                auto & node = level.front();
                notVisited.erase(node);

                for(const auto & word : notVisited)
                {
                    if(nextTo(node, word))
                    {
                        if(word == endWord) return depth+1;
                    
                        level.push(word);
                    }
                }
                level.pop();
            }
            ++depth;
        }
        return 0;
    }
    
private:
    bool nextTo(const string & left, const string & right)
    {
        bool isNextTo = false;
        int count = 0;
        {
            for(size_t i = 0; i<left.size()&&count<=1; ++i)
            {
                if(left[i] != right[i]) ++count;
            }
            isNextTo =  count == 1;
        }
        return isNextTo;
    }  
    
};
