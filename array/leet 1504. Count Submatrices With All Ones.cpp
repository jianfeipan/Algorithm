// accumute lines, then becomes max 1's in histogram, with a monoton stack!!

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), ans = 0;
        vector<int> height(c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) height[j] = mat[i][j] ? height[j] + 1 : 0;// histogram!!!!

            vector<int> sum(c);
            stack<int> increasing;
            for (int j = 0; j < c; j++) {
                while (!increasing.empty() && height[increasing.top()] >= height[j]) increasing.pop();
                // for hight_j, it can extend to most left to p or -1
                // count the number using i, j as the right bottom point: height_j * len, where len = j-p
                // basically how may 1's can build rectangle woth [i,j], before that we have sum[p], so plus it
                if (!increasing.empty()) {
                    int p = increasing.top();
                    sum[j] = sum[p] + height[j] * (j - p);
                } else {
                    sum[j] = height[j] * (j + 1);
                }

                increasing.push(j);

                ans += sum[j];
            }
        }
        return ans;
    }
};
