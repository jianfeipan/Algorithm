class Solution {
private:
    constexpr static array<pair<int, int>, 4> DIRECTIONS = {{
        { 1,0},
        {-1,0},
        {0, 1},
        {0,-1}
    }};

    void dfs_mark_higher_land(
        int r, 
        int c, 
        vector<vector<int>>& marked, 
        const vector<vector<int>>& heights){

        auto valid = [&](int r, int c){
            const auto R = heights.size();
            const auto C = heights[0].size();
            if(r<0 || r>=R || c<0 || c>=C) return false;
            if(marked[r][c]) return false;

            return true;
        };
        
        marked[r][c] = 1;
        for(auto [dr, dc] : DIRECTIONS){
            auto new_r = r+dr;
            auto new_c = c+dc;
            if(valid(new_r,new_c)){
                if(heights[new_r][new_c] >= heights[r][c]){// flowing up!
                    dfs_mark_higher_land(new_r, new_c, marked, heights);
                }
            }
        } 
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const auto R = heights.size();
        const auto C = heights[0].size();

        vector<vector<int>> top_left(R, vector<int>(C, 0));
        // mark_from_top_left(top_left, heights);
        {
            for(int r=0; r<R; ++r) dfs_mark_higher_land(r, 0, top_left, heights);
            for(int c=0; c<C; ++c) dfs_mark_higher_land(0, c, top_left, heights);
        }

        vector<vector<int>> bottom_right(R, vector<int>(C, 0));
        //mark_from_bottom_right(top_left, heights);
        {
            for(int r=0; r<R; ++r) dfs_mark_higher_land(r, C-1, bottom_right, heights);
            for(int c=0; c<C; ++c) dfs_mark_higher_land(R-1, c, bottom_right, heights);
        }

        vector<vector<int>> res;
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                if(top_left[r][c] && bottom_right[r][c]) res.push_back({r, c});
            }
        }
        return res;
    }
};
