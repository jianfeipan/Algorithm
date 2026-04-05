class Solution {
private:
    bool isLadder(const string& left, const string& right){
        //assert(left.size() == right.size())
        int diff = 0;
        for(int i=0; i<left.size(); ++i){
            if(left[i]!=right[i]){
                ++diff;
                if(diff>1) return false;
            }
        }
        return diff == 1;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.push_back(beginWord); // cat could be not in the list
        // dont add end word, the prompt says if end is not in, it's 0
        const auto& n = wordList.size();
        unordered_map<string, unordered_set<string>> adj;
        // for(int i=0; i<n; ++i){ // O(M*N^2)
        //     for(int j=i+1; j<n; ++j){
        //         if(isLadder(wordList[i], wordList[j])){
        //             adj[wordList[i]].insert(wordList[j]);
        //             adj[wordList[j]].insert(wordList[i]);
        //         }
        //     }
        // }
        unordered_set<string> dict(wordList.begin(), wordList.end());
        for(const auto& word : wordList){ // O(N*M)!!!!
            auto newWord = word;
            for(int i=0; i<word.size(); ++i){
                auto backUp = word[i];
                for(int j = 0; j<26; ++j){
                    auto newLetter = 'a'+j;
                    if(newLetter!=backUp){
                        newWord[i] = newLetter;
                        if(dict.count(newWord)) adj[word].insert(newWord);
                    }
                }
                newWord[i] = backUp;
            }
        }


        // BFS: neighbor is one letter diff: symmetric
        queue<string> bfs;
        unordered_set<string> visited;
        visited.insert(beginWord);
        bfs.push(beginWord);
        int steps = 0;
        while(!bfs.empty()){
            ++steps;
            const auto levelSize = bfs.size();
            for(int i=0; i<levelSize; ++i){
                const auto current = bfs.front(); bfs.pop();
                //cout<< "next for: "<< current <<endl;
                if(current == endWord) return steps;
                for(const auto& next : adj[current]){
                    if(!visited.count(next)){
                        //cout<< next <<", ";
                        visited.insert(next);
                        bfs.push(next);
                    }
                }
            }
        }
        return 0; // not fund
        
    }
};
