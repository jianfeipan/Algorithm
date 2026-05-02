    /*
    
    
    
    [["A","B","C","E"],
     ["S","F","E","S"],
     ["A","D","E","E"]]
    
    "ABCESEEEFS"
    
    
    */
 class Solution {
private:
    constexpr static array<array<int, 2>, 4> DIRECTIONS{{
        {-1,  0},
        {+1,  0},
        { 0, -1},
        { 0, +1},
    }};

    bool dfs(vector<vector<char>>& board, 
            int r,
            int c,
            int index, 
            const string& word){
        const auto& R = board.size();
        const auto& C = board[0].size();   

        if(index == word.size()) return true;    
        if( r<0 || r>=R || c<0 || c>=C) return false;
        if(board[r][c] != word[index]) return false;

        auto backup = board[r][c];
        board[r][c] = '.'; // visited
        for(const auto& [dr, dc] : DIRECTIONS){
            if(dfs(board, r+dr, c+dc, index+1, word)) return true;
        }
        board[r][c] = backup;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        const auto& R = board.size();
        const auto& C = board[0].size();
        for(int r = 0; r<R; ++r){
            for(int c = 0; c<C; ++c){
                if(dfs(board, r, c, 0, word)) return true;
            }
        }
        return false;
    }
};
