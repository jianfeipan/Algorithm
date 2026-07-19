class Trie
{
public:
    Trie() = default;
    
    void insert(const string & s)
    {
        Trie * current = this;
        for(char c : s)
        {
            if(!current->next[c-'a'])
                current->next[c-'a'].reset(new Trie());
            current =  current->next[c-'a'].get();
        }
        current->isWord = true;
    }

    array<unique_ptr<Trie>,26> next;
    bool isWord;

};


class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> concatenated;
        
        Trie prefixTree;
        for(const auto & word : words) prefixTree.insert(word);
        
        for(const auto & word : words)
        {
            if(isConcatenated(word, 0, &prefixTree)) concatenated.push_back(word);
        }
        return concatenated;
    }
    
private:
    bool isConcatenated(const string & word, size_t from, Trie * wordsRoot)
    {       
        const size_t start = from;
        const Trie * current = wordsRoot;

        for(; from<word.size(); ++from)
        {
            Trie * next = current->next[word[from] - 'a'].get();
            if(next) 
            {
                current = next; 
                if(current->isWord)
                {
                    if(from < word.size()-1 && isConcatenated(word, from+1, wordsRoot)) return true;
                }
            }
            else return false;
        }

        return start >0 && current->isWord;
    }
    


};
