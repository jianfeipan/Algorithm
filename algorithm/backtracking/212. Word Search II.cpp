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
#include <array>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {

private:
    struct TrieNode{
        array<TrieNode*, 26> next;
        string const* word = nullptr;
        TrieNode(){
            for (int i = 0; i < 26; ++i) {
                next[i] = nullptr;
            }
        }
    };

    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        {1, 0},
        {-1,0},
        {0, 1},
        {0,-1}
    }};

    void addWord(const string& s, int pos, TrieNode& root){
        if(pos == s.size()) { root.word = &s; return; }
        auto c = s[pos];
        if(root.next[ c - 'a'] == nullptr){
            root.next[ c - 'a'] = new TrieNode();
        }
        addWord(s, pos+1, *(root.next[ c - 'a']));
    }

    void dfs(vector<vector<char>>& board,
            int r, int c,
            TrieNode* root, vector<string>& fund){

        if(!root) return;

        if(root->word) {
            fund.push_back(*(root->word));
            root->word = nullptr; // avoid duplicates
        }
        // dfs neighbors, four directions and visited mark
        for(const auto&[dr, dc] : DIRECTIONS){
            auto newR = r+dr;
            auto newC = c+dc;
            if(newR<board.size()
            && newR>=0
            && newC<board[newR].size()
            && newC>=0 && board[newR][newC]!='.'){
                auto next = board[newR][newC];
                board[newR][newC] = '.';
                dfs(board, newR, newC, root->next[next - 'a'], fund);
                board[newR][newC] = next;// backtrace
            }
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode root;
        for(const auto& word : words) addWord(word, 0, root);

        vector<string> fund;
        for(int r=0; r<board.size(); ++r){
            for(int c=0; c<board[r].size(); ++c){
                auto current = board[r][c];
                board[r][c] = '.';
                dfs(board, r, c, root.next[current - 'a'], fund);
                board[r][c] = current;
            }
        }

        return fund;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words = {"oath", "pea", "eat", "rain"};
    auto result = sol.findWords(board, words);
    cout << "Found words: ";
    for (const auto& w : result) cout << w << " ";
    cout << endl;

    // Test 2: empty board
    vector<vector<char>> board2 = {};
    vector<string> words2 = {"xoxo"};
    auto result2 = sol.findWords(board2, words2);
    cout << "Found words (empty board): ";
    for (const auto& w : result2) cout << w << " ";
    cout << endl;

    return 0;
}

