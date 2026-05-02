class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());

        if(!words.count(endWord)) return 0;

        //BFS
        queue<string> q;
        unordered_set<string> visited;

        q.push(beginWord);
        visited.insert(beginWord);
        int steps = 0;
        while(!q.empty()){
            ++steps;
            
            const auto level_size = q.size();
            for(int j=0; j<level_size; ++j){
                auto current = q.front(); q.pop();
                if(current == endWord) return steps; // found!

                for(int i=0; i<current.size(); ++i){
                    auto next = current;
                    for(char c='a'; c<='z'; ++c){// a -> z
                        next[i] = c;
                        if(!visited.count(next) && words.count(next)){
                            visited.insert(next);
                            q.push(next);
                        }
                    }
                }
            }
        }

        return 0;
    }
};
/*
Word Ladder
Hard Topics Company Tags
Hints

You are given two words, beginWord and endWord, and also a list of words wordList. All of the given words are of the same length, consisting of lowercase English letters, and are all distinct.

Your goal is to transform beginWord into endWord by following the rules:

    You may transform beginWord to any word within wordList, provided that at exactly one position the words have a different character, and the rest of the positions have the same characters.
    You may repeat the previous step with the new word that you obtain, and you may do this as many times as needed.

Return the minimum number of words within the transformation sequence needed to obtain the endWord, or 0 if no such sequence exists.

Example 1:

Input: beginWord = "cat", endWord = "sag", wordList = ["bat","bag","sag","dag","dot"]

Output: 4

Explanation: The transformation sequence is "cat" -> "bat" -> "bag" -> "sag".

Example 2:

Input: beginWord = "cat", endWord = "sag", wordList = ["bat","bag","sat","dag","dot"]

Output: 0

 */