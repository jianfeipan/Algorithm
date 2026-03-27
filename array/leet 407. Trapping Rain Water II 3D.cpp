
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) return 0;

        const int  R = heightMap.size();
        const int C = heightMap[0].size();
        if (R < 3 || C < 3) return 0;
        
        using T = tuple<int,int,int>;
        vector<vector<bool>> visited(R, vector<bool>(C, false));

        // push all boundry cells to the minHeap 
        priority_queue<T, vector<T>, greater<T>> boundries;
        for (int i = 0; i < R; ++i) {
            boundries.emplace(heightMap[i][0], i, 0); visited[i][0] = true;
            boundries.emplace(heightMap[i][C-1], i, C-1); visited[i][C-1] = true;
        }
        for (int j = 0; j < C; ++j) {
            if (!visited[0][j]) { boundries.emplace(heightMap[0][j], 0, j); visited[0][j] = true; }
            if (!visited[R-1][j]) { boundries.emplace(heightMap[R-1][j], R-1, j); visited[R-1][j] = true; }
        }



        int res = 0;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        // traversal all unvisited cells, if the new one is smaller the current one
        while (!boundries.empty()) {
            auto [h, r, c] = boundries.top(); boundries.pop();
            for (auto &d : dirs) { // visit 4 direction
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr < 0 || nr >= R || nc < 0 || nc >= C || visited[nr][nc]) continue;
                visited[nr][nc] = true;

                int nh = heightMap[nr][nc];

                if (nh < h) 
                    res += (h - nh);
                //nh will trap water, then we deal nh as h to be a part of the bountry in the queue.
                boundries.emplace(max(nh, h), nr, nc);
            }
        }
        return res;
    }
};
