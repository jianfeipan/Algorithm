class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) 
    {
        /*
        DFS mark one island
        
        find boundries
        
        BFS from all boundries to find another island---> scan whole map to avoid from point
        */
        
        for (int i = 0, found = 0; !found && i < grid.size(); ++i)
        {
            for (int j = 0; !found && j < grid[0].size(); ++j)
            {
                found = paint(grid, i, j);
            }
        }
        
        for (int len = 2; ; ++len)
            
        for (int i = 0; i < grid.size(); ++i)
            for (int j = 0; j < grid[0].size(); ++j) 
                if (grid[i][j] == len 
                    && (expand(grid, i - 1, j, len) 
                         || expand(grid, i, j - 1, len) 
                         || expand(grid, i + 1, j, len) 
                         || expand(grid, i, j + 1, len)))
                        return len - 2;
        
    }
    
private:  
    int paint(vector<vector<int>>& A, int i, int j) 
    {
        if (i < 0 || j < 0 || i == A.size() || j == A.size() || A[i][j] != 1) return 0;
        
        A[i][j] = 2;
        return 1 + paint(A, i + 1, j) + paint(A, i - 1, j) + paint(A, i, j + 1) + paint(A, i, j - 1);
    }
    
    bool expand(vector<vector<int>>& A, int i, int j, int len) 
    {
        if (i < 0 || j < 0 || i == A.size() || j == A.size()) return false;
        
        if (A[i][j] == 0) A[i][j] = len + 1;
        return A[i][j] == 1;
    }      

};
