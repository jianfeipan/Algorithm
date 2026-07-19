/*
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

prefix sum, from [x1,y1] -> [x2,y2]
m*n*n

*/
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        const int R = matrix.size(), C = matrix[0].size();
        for (int r = 0; r < R; ++r)
            for (int c = 1; c < C; ++c)
                matrix[i][j] += matrix[i][j - 1];
        
        int res = 0
        unordered_map<int, int> counter;
        //O(R*C*C)
        for(int l = 0; l<C; ++l){
            for(int r = c; r<C; ++r){
                counter = {{0, 1}};
                int sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum += matrix[k][r] - (l > 0 ? matrix[k][l - 1] : 0);
                    auto prevSum = sum - target;
                    res += counter.count(prevSum) ? 
                            counter[prevSum] : 0;
                    ++counter[cur];
                }
            }
        }

        return res;

    }   
};
