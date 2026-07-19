class Solution {
public:
    /**
     * @param board: a board
     * @param click: the position
     * @return: the new board
     */


     /*
     
     
     Description
Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:

If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
        [
            "EEEEE",
            "EEMEE",
            "EEEEE",
            "EEEEE"
        ]

        [
            "B1E1B",
            "B1M1B",
            "B111B",
            "BBBBB"
        ]
     
     */
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) 
    {
        if(board.empty() || board[0].empty())
            throw new std::invalid_argument( "empty board" );

        switch (board[click[0]][click[1]])
        {
            case 'M':
            {
                board[click[0]][click[1]] = 'X';
                break;
            }
            case 'E':
            {
                visiteUnresolved(board, click);
            }
            default:
            break;

        }

        return board;
    }

    

private:
    void visiteUnresolved(vector<vector<char>>& board, const vector<int>& click)
    {
        const size_t adjacentMinesCount = countAdjacentMines(board, click);
        if(adjacentMinesCount == 0)
        {
            board[click[0]][click[1]] = 'B';
            for(const auto & d : getDirections())
            {
                const int x = click[0] + d.first;
                const int y = click[1] + d.second;

                if(x>=0 && x<board.size() && y>=0 && y<board[0].size())
                {
                    if(board[x][y]=='E')
                    {
                        visiteUnresolved(board, {x, y});
                    }
                }
            }
        }
        else
        {
            board[click[0]][click[1]] = '0'+ adjacentMinesCount;
        }
    }

    size_t countAdjacentMines(const vector<vector<char>>& board, const vector<int>& click)
    {
        size_t count = 0;
        for(const auto & d : getDirections())
        {
            const int x = click[0] + d.first;
            const int y = click[1] + d.second;

            if(x>=0 && x<board.size() && y>=0 && y<board[0].size())
            {
                if(board[x][y]=='M')
                    ++count;
            }
        }
        return count;
    }

    static const vector<pair<int, int>> getDirections()
    {
        static const std::vector<std::pair<int, int>> directions ({ {-1, 0}, {-1, -1}, {-1, 1}, {1,0}, {1, -1}, {1,1},{0, -1}, {0, 1} });
        return directions;
    }


};
