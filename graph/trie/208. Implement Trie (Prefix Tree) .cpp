/*A prefix tree (also known as a trie) is a tree data structure used to efficiently store and retrieve keys in a set of strings. Some applications of this data structure include auto-complete and spell checker systems.

Implement the PrefixTree class:

PrefixTree() Initializes the prefix tree object.
void insert(String word) Inserts the string word into the prefix tree.
boolean search(String word) Returns true if the string word is in the prefix tree (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
Example 1:

Input:
["Trie", "insert", "dog", "search", "dog", "search", "do", "startsWith", "do", "insert", "do", "search", "do"]

Output:
[null, null, true, false, true, null, true]

Explanation:
PrefixTree prefixTree = new PrefixTree();
prefixTree.insert("dog");
prefixTree.search("dog");    // return true
prefixTree.search("do");     // return false
prefixTree.startsWith("do"); // return true
prefixTree.insert("do");
prefixTree.search("do");     // return true
Constraints:

1 <= word.length, prefix.length <= 1000
word and prefix are made up of lowercase English letters.*/
#include<array>
class PrefixTree {
private:
    struct Node{
        //unordered_map<char, unique_ptr<Node>> children;
        array<Node*, 26> children{};
        bool is_word; 
    };

    Node* newNode(){
        pool.emplace_back();
        return &pool.back();
    }

    Node* root;
    vector<Node> pool; // memory pool!! 
public:
    PrefixTree() {
        constexpr static size_t CAPACITY = 1024;
        pool.reserve(CAPACITY);
        root = newNode();
    }
    
    void insert(string word) {
        Node* cur = root;
        for(auto c : word) {
            auto index = c-'a';
            if(!cur->children[index]) cur->children[index] = newNode();
            cur = cur->children[index];
        }
        cur->is_word = true;
    }
    
    bool search(string word) {
        Node* cur = root;
        for(auto c : word) {
            auto index = c-'a';
            if(!cur->children[index]) return false;
            cur = cur->children[index];
        }
        return cur->is_word;
    }
    
    bool startsWith(string prefix) {
        Node* cur = root;
        for(auto c : prefix) {
            auto index = c-'a';
            if(!cur->children[index]) return false;
            cur = cur->children[index];
        }
        return true;
    }
};
