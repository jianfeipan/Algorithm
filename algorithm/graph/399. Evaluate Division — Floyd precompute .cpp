#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

/*
399. Evaluate Division — Floyd-Warshall approach

Precompute all-pairs results in O(V^3), then answer each query in O(1).
dist[i][j] = value of variable_i / variable_j
*/

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // Map variable names to indices
        unordered_map<string, int> id;
        int n = 0;
        for(auto& eq : equations){
            if(!id.count(eq[0])) id[eq[0]] = n++;
            if(!id.count(eq[1])) id[eq[1]] = n++;
        }

        // Initialize dist matrix: dist[i][j] = i / j, -1 means unknown
        vector<vector<double>> dist(n, vector<double>(n, -1.0));
        for(int i = 0; i < n; ++i) dist[i][i] = 1.0;

        for(int i = 0; i < (int)equations.size(); ++i){
            int u = id[equations[i][0]], v = id[equations[i][1]];
            dist[u][v] = values[i];
            dist[v][u] = 1.0 / values[i];
        }

        // Floyd-Warshall: if i/k and k/j are known, then i/j = (i/k) * (k/j)
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if(dist[i][k] > 0 && dist[k][j] > 0 && dist[i][j] < 0)
                        dist[i][j] = dist[i][k] * dist[k][j];

        vector<double> ans;
        ans.reserve(queries.size());
        for(auto& q : queries){
            auto it0 = id.find(q[0]), it1 = id.find(q[1]);
            if(it0 == id.end() || it1 == id.end())
                ans.push_back(-1.0);
            else
                ans.push_back(dist[it0->second][it1->second]);// O(1)!
        }
        return ans;
    }
};

int main() {
    Solution sol;

    // Test 1: a/b=2.0, b/c=3.0
    {
        vector<vector<string>> equations = {{"a","b"},{"b","c"}};
        vector<double> values = {2.0, 3.0};
        vector<vector<string>> queries = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
        auto res = sol.calcEquation(equations, values, queries);
        assert(abs(res[0] - 6.0) < 1e-9);
        assert(abs(res[1] - 0.5) < 1e-9);
        assert(res[2] == -1.0);
        assert(abs(res[3] - 1.0) < 1e-9);
        assert(res[4] == -1.0);
        cout << "Test 1 passed" << endl;
    }

    // Test 2
    {
        vector<vector<string>> equations = {{"a","b"},{"b","c"},{"bc","cd"}};
        vector<double> values = {1.5, 2.5, 5.0};
        vector<vector<string>> queries = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};
        auto res = sol.calcEquation(equations, values, queries);
        assert(abs(res[0] - 3.75) < 1e-9);
        assert(abs(res[1] - 0.4) < 1e-9);
        assert(abs(res[2] - 5.0) < 1e-9);
        assert(abs(res[3] - 0.2) < 1e-9);
        cout << "Test 2 passed" << endl;
    }

    cout << "All tests passed!" << endl;
    return 0;
}
