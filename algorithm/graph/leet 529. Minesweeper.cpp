class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        vector<vector<char>> updated(board);
        
        const int row = click[0];
        const int col = click[1];

        const char & input = board[row][col];  
        
        switch(input)
        {
            case 'M':
                updated[row][col] = 'X';
                break;
            case 'E':
                visitBlanks(updated, row, col);
                break;
            default:
                break;
        }
        return updated;
    }
    
private:
    void visitBlanks(vector<vector<char>> & board, int row, int col)
    {    
        if(board[row][col] == 'E')
        {
            const size_t mines = countMines(board, row, col);
            if(mines == 0)
            {
                board[row][col] = 'B';
                const vector<pair<int, int>> & directions = eightDirections();

                for(const auto & dir : directions)
                {
                    const int nextRow = row + dir.first;
                    const int nextCol = col + dir.second;
                    if(0<=nextRow && nextRow<board.size() && 0<=nextCol && nextCol<board[0].size())
                    {
                        if(board[nextRow][nextCol] == 'E')
                            visitBlanks(board, nextRow, nextCol);
                    }
                }
            }
            else board[row][col] = ('0'+mines);
            
        }
    }
    
    
    size_t countMines(const vector<vector<char>> & board, int row, int col)
    {
        size_t count = 0;
        
        const vector<pair<int, int>> & directions = eightDirections();
        
        for(const auto & dir : directions)
        {
            const int nextRow = row + dir.first;
            const int nextCol = col + dir.second;
            
            if(0<=nextRow && nextRow<board.size() && 0<=nextCol && nextCol<board[0].size())
            {
                if(board[nextRow][nextCol] == 'M') ++count;
            }
        }
        
        return count;
    }
    
    static const vector<pair<int, int>> & fourDirections()
    {
        static const vector<pair<int, int>> four({
            {-1,  0},
            { 1,  0},
            { 0,  1},
            { 0, -1}
        });
        return four;
    }
    
    static const vector<pair<int, int>> & eightDirections()
    {
        static const vector<pair<int, int>> eight({
            {-1,  0},
            { 1,  0},
            { 0,  1},
            { 0, -1},
            {-1, -1},
            { 1,  1},
            {-1,  1},
            { 1, -1}
        });
        return eight;
    }
    
};
