class WordDictionary {
private:
    struct Node{
        unordered_map<char, Node> children;
        bool is_word {false};
    };

    Node root;

    bool search(Node* root, string_view word, int from) {
        if (from == word.size()) return root->is_word;
        
        const auto& cur = word[from];
        if (cur == '.') {
            for(auto& [_, node] : root->children) {
                if(search(&node, word, from+1)) return true;
            }
            return false;
        } else {
            if (!root->children.count(cur)) return false;
            return search(&(root->children[cur]), word, from+1);
        }
    }
public:
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        auto* current = &root;
        for (const auto& c : word) {
            current = &(current->children[c]);
        }
        current->is_word = true;
    }
    
    bool search(string word) {
        if (word.empty()) return false;
        return search(&root, word, 0);
    }
};


/*
Design a data structure that supports adding new words and searching for existing words.

Implement the WordDictionary class:

    void addWord(word) Adds word to the data structure.
    bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.

Example 1:

Input:
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["day"],["bay"],["may"],["say"],["day"],[".ay"],["b.."]]

Output:
[null, null, null, null, false, true, true, true]

Explanation:
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("day");
wordDictionary.addWord("bay");
wordDictionary.addWord("may");
wordDictionary.search("say"); // return false
wordDictionary.search("day"); // return true
wordDictionary.search(".ay"); // return true
wordDictionary.search("b.."); // return true
     */