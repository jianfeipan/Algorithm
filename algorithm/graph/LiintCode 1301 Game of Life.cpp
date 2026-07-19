class Solution {
public:
    /**
     * @param board: the given board
     * @return: nothing
     */
    void gameOfLife(vector<vector<int>> &board) {
        //idea1: we can copy the board, then write to the new one by reading the old one
        //idea2: or we can read input map and generate coordinates for changes
        if(board.empty()||board[0].empty())
            return;

        const vector<vector<int>> original(board);

        for(size_t line = 0; line<board.size(); ++line)
        {
            for(size_t col = 0; col<board[0].size(); ++ col)
            {
                life(line, col, board, original);
            }
        }

    }

private:
    void life(size_t line, size_t col, vector<vector<int>> & board, const vector<vector<int>> & original)
    {
        const size_t liveNeighborsCount = countliveNeighbors(line, col, original); 
        if(original[line][col] == 1)
        {
            if(liveNeighborsCount<2 || liveNeighborsCount>3) board[line][col] = 0;
            else board[line][col] = 1;
        }
        else if(original[line][col] == 0)
        {
            if(liveNeighborsCount == 3)
                board[line][col] = 1;
        }
        else
        {
            throw new  std::invalid_argument("Bad value in map");
        }
    }
    
    bool isValidate(int line, int col, size_t linCount, size_t colCount)
    {
        return line>=0 
        && line<=linCount-1 
        && col>=0 
        && col<=colCount-1;
    }
    
    size_t countliveNeighbors(int line, int col, const vector<vector<int>> & board)
    {
        size_t count = 0;
        for(const auto & direction : _directions())
        {
            const int nLine = line + direction.first;
            const int nCol = col + direction.second;
            if(isValidate(nLine, nCol, board.size(), board[0].size()))
            {
                count+=board[nLine][nCol];
            }
        }
        return count;
    }
private:
    const std::vector<std::pair<int, int>> & _directions()
    {
        static const std::vector<std::pair<int, int>> directions ({ {-1, 0}, {-1, -1}, {-1, 1}, {1,0}, {1, -1}, {1,1},{0, -1}, {0, 1} });
        return directions;
    }
};

