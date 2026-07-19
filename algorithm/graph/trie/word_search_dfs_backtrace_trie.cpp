class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        { 1, 0},
        {-1, 0},
        {0,  1},
        {0, -1},
    }};

    struct Node{
        array<unique_ptr<Node>, 26> children {};
        string* word {nullptr};
    };   

    void dfs(vector<vector<char>>& board,
             int r, int c,
             Node* root,
             vector<string>& res) {

        const auto& n_row = board.size();
        const auto& n_col = board[0].size();

        if (!root || r<0 || r>=n_row || c<0 || c>= n_col ) return;

        if (board[r][c] == '.') return; // is visited

        auto& next_node = root->children[board[r][c] - 'a'];
        if (!next_node) return; // no such letter


        if (next_node->word) {
            res.push_back(*(next_node->word));
            next_node->word = nullptr; // Prevent duplicates and dangling references
        }

        auto backup = board[r][c];
        board[r][c] = '.'; // visited
        for (const auto& [dr, dc] : DIRECTIONS) {
            dfs(board, r+dr, c+dc, next_node.get(), res);
        }
        board[r][c] = backup; // backtracing
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Node root;
        // read words
        for(auto& word : words) {
            auto* current = &root;
            for (auto& c : word) {
                auto& next = current->children[c-'a'];
                if (!next) next = make_unique<Node>();
                current = next.get();
            }
            current->word = &word;
        }

        vector<string> res;
        const auto& n_row = board.size();
        const auto& n_col = board[0].size();
        for(int r = 0; r < n_row; ++r) {
            for(int c = 0; c < n_col; ++c) {
                dfs(board, r, c, &root, res);
            }
        }

        return res;
    }
};
