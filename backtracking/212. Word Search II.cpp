/*

212. Word Search II

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.



Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []


*/
/*
idea:
    loop on words
    -> findWord()
        loop on the board find match of the first letter
        from that one DFS
            findWordFrom(current position, current letter index, word, visited)
                when rach the end -> return true



*/
constexpr array<array<int, 2>, 4> DIRECTIONS{{
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
}};
class Solution_dfs {
private:
    bool dfs(const vector<vector<char>>& board, const string& word,
            int index, int row, int col, vector<vector<bool>>& visited)
    {
        if(index == word.size()) return true;

        for(const auto& [dr, dc] : DIRECTIONS){
            int r = row+dr;
            int c = col+dc;
            if(r<board.size() && r>=0
               && c<board[0].size() && c>=0
               && !visited[r][c]
               && board[r][c] == word[index]){
                visited[r][c] = true;
                if(dfs(board, word, index+1, r, c, visited)) return true;
                visited[r][c] = false;
            }
        }
        return false;
    }

    bool findWord(const vector<vector<char>>& board, const string& word){
        for(int r=0; r<board.size(); ++r){
            for(int c=0; c<board[r].size(); ++c){
                if(board[r][c] == word[0]){
                    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
                    visited[r][c] = true;
                    if(dfs(board, word, 1, r, c, visited)){
                        return true;
                    }
                }
            }
        }

        return false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> found;

        for(const auto& word : words){
            if(findWord(board, word)){
                found.push_back(word);
            }
        }

        return found;
    }
};

class Solution{// Trie + DFS
struct TrieNode {
    array<TrieNode*, 26> children{};
    string* word = nullptr; // store the word at the end node
};

private:
    void insertWord(TrieNode* root, string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->word = &word;
    }
    void dfs(const vector<vector<char>>& board, TrieNode* node,
            int row, int col, vector<vector<bool>>& visited, vector<string>& found)
    {   
        if(!node) return;
        
        if(node->word){
            found.push_back(*node->word);
            node->word = nullptr; // avoid duplicate
        }

        for(const auto& [dr, dc] : DIRECTIONS){
            int r = row+dr;
            int c = col+dc;
            if(r<board.size() && r>=0
               && c<board[0].size() && c>=0
               && !visited[r][c]){
                char nextChar = board[r][c];
                int index = nextChar - 'a';
                if(node->children[index]){
                    visited[r][c] = true;
                    dfs(board, node->children[index], r, c, visited, found);
                    visited[r][c] = false;
                }
            }
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        const auto ROW = board.size();
        const auto COL = board[0].size();

        vector<string> found;

        TrieNode* root = new TrieNode();
        for(auto& word : words){
            insertWord(root, word);
        }

        vector<vector<bool>> visited(ROW, vector<bool>(COL, false));
        for(int r=0; r<ROW; ++r){
            for(int c=0; c<COL; ++c){
                char ch = board[r][c];
                int index = ch - 'a';
                if(root->children[index]){
                    visited[r][c] = true;
                    dfs(board, root->children[index], r, c, visited, found);
                    visited[r][c] = false;
                }
            }
        }

        return found;
    }
};

/*

board =
[["a","b","c"],
 ["a","e","d"],
 ["a","f","g"]]
words =
["abcdefg","gfedcbaaa","eaabcdgfa","befa","dgc","ade"]

Use Testcase
Output
["abcdefg","gfedcbaaa","befa"]
Expected
["abcdefg","befa","eaabcdgfa","gfedcbaaa"]

*/
