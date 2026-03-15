/*
733. Flood Fill

You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:

Begin with the starting pixel and change its color to color.
Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
The process stops when there are no more adjacent pixels of the original color to update.
Return the modified image after performing the flood fill.

 

Example 1:

Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2

Output: [[2,2,2],[2,2,0],[2,0,1]]

Explanation:



From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.

Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.

Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0

Output: [[0,0,0],[0,0,0]]

Explanation:

The starting pixel is already colored with 0, which is the same as the target color. Therefore, no changes are made to the image.

 

Constraints:

m == image.length
n == image[i].length
1 <= m, n <= 50
0 <= image[i][j], color < 216
0 <= sr < m
0 <= sc < n
*/


class Solution {
private:
    constexpr const static array<array<int, 2>, 4> _directions = {{
        {-1,0},
        { 1,0},
        {0,-1},
        {0, 1}
    }};
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        // DFS/BFS: 4 direction neighbers, check if they are the same value, then color it.
        const int& R = image.size();
        const int& C = image[0].size();

        if(sr<0 || sr>=R || sc<0 || sc> C) return {}; // invalid input sr,sc out of boundry.
        
        const int& originalColor = image[sr][sc];
        if(originalColor==color) return image;

        vector<vector<int>> res = image;
        vector<vector<bool>> visited(R, vector<bool>(C, false));

        using Row = int;
        using Col = int;
        std::queue<pair<Row, Col>> q;

        q.push({sr, sc});
        res[sr][sc] = color;
        visited[sr][sc]=true;
        while(!q.empty()){
            const auto [r, c] = q.front();
            q.pop();

            for(const auto& direction : _directions){
                int newR = r+direction[0];
                int newC = c+direction[1];
                if(newR>=0 && newR<R 
                && newC>=0 && newC<C 
                && res[newR][newC] == originalColor){ // not visited
                    res[newR][newC] = color;
                    q.push({newR, newC});
                }
            }
        }
        return res;
    }
};
