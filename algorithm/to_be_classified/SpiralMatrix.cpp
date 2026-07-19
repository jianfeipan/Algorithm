class spiralMatrix {
    
private:
    static bool isVisited(int visit)
    {
        return visit < -100;
    }
    
    static void setVisited(int & visit)
    {
        visit = -101;
    }
    
    static void move(int & x, int & y, int & direction, const vector<vector<int>>& matrix)
    {
        if(direction == 0)
        {
            if(x>=matrix[0].size()-1 || isVisited(matrix[y][x+1]))
            {
                direction=1;
                y++;
            }
            else{
                x++; 
            }
        }
        else if( direction == 1)
        {
            if(y>=matrix.size()-1 || isVisited(matrix[y+1][x]))
            {
                direction=2;
                x--;
            }
            else{
                y++; 
            }

        }
        else if( direction == 2)
        {
            if(x<=0 || isVisited(matrix[y][x-1]))
            {
                direction=3;
                y--;
            }
            else{
                x--; 
            }   
        }
        else if( direction == 3)
        {   
            if(y<=0 || isVisited(matrix[y-1][x]))
            {
                direction=0;
                x++;
            }
            else{
                y--; 
            }  

        }
                
    }

    
    
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int x=0;
        int y = 0;

        vector<int> res;
        res.reserve(matrix.size()*matrix[0].size());
        
        int direction = 0; //0>; 1v; 2<; 3^
        
        for(int i = 0; i <  res.capacity(); i++)
        {
            res.push_back(matrix[y][x]);
            setVisited(matrix[y][x]);
            
            move(x, y, direction, matrix);
            
        }
        
        return res;
        
    }
};
