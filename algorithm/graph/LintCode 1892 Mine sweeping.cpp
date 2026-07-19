class Solution {
public:
    /**
     * @param Mine_map: an matrix represents the map.
     * @param Start: the start position.
     * @return: return an array including all reachable positions.
     */
    vector<vector<int>> Mine_sweeping(vector<vector<int>> &Mine_map, vector<int> &Start) {
        /*
        [
            [1,0,0,0],
            [1,0,0,0],
            [0,1,1,1],
            [0,1,0,0]
        ]
        */
        vector<vector<int>> result;
        vector<vector<bool>> visited(Mine_map.size(), vector<bool>(Mine_map[0].size(), false));
        visite(Start, Mine_map, visited, result);
        return result;
    }

private:
    void visite(const vector<int> & start, const vector<vector<int>> & Mine_map, vector<vector<bool>> & visited, vector<vector<int>> & result)
    {
        const int x = start[0];
        const int y = start[1];
        if(!visited[x][y])
        {
            result.push_back(start);
            visited[x][y] = true;
            if(Mine_map[x][y]==1)
            {
                if(x>0)//up
                {
                    visite({x-1,y}, Mine_map, visited, result);
                }
                
                if(x<Mine_map.size()-1)//down
                {
                    visite({x+1, y}, Mine_map, visited, result);
                }

                if(y>0)//left
                {
                    visite({x, y-1}, Mine_map, visited, result);
                }

                if(y<Mine_map[0].size()-1)//right
                {
                    visite({x, y+1}, Mine_map, visited, result);
                }
            }
        }
    }

};
