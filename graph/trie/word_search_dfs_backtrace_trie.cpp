class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        { 1, 0},
        {-1, 0},
        {0,  1},
        {0, -1},
    }};

    struct Node{
        array<Node*, 26> children{};
        unique_ptr<string> word{};
    };

    class Trie{
    private:

        vector<Node> pool;// vector can be relocated to another address, the org pointers are dungling

        Node* newNode(){
            pool.emplace_back();
            return &pool.back();
        }
    public:
        Node* root;
        Trie() {
            //pool.reserve(1024);
            root = newNode();
        }

        void add(const string& word){
            auto cur = root;
            for(auto c : word){
                int index = c - 'a';
                if(!cur->children[index]) cur->children[index] = newNode();
                cur = cur->children[index];
            }
            cur->word = make_unique<string>(word);
        }
    };
   
    void search(int r, int c,
                vector<vector<char>>& board, 
                Node* root,
                vector<string>& found){
        if(!root) return;

        const auto R = board.size();
        const auto C = board[0].size();
        if(r<0 || r>=R || c<0 || c>=C) return;

        auto letter = board[r][c];
        if(letter == '.') return;// visited

        auto next = root->children[letter - 'a'];
        if(!next) return;
        
        board[r][c] = '.'; 
        {
            if(next->word) { 
                found.push_back(*(next->word));
                next->word.reset(); // avoid duplications
            }

            for(const auto& [dr, dc] : DIRECTIONS){
                search(r+dr, c+dc, board, next, found);
            } 
        }
        board[r][c] = letter; // backtracing
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for(const auto& word : words) trie.add(word);

        vector<string> found;
        for(int r = 0; r < board.size(); ++r){
            for(int c = 0; c < board[0].size(); ++c){
                search(r, c, board, trie.root, found);
            }
        }
        return found;
    }
};
