#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

/*
399. Evaluate Division

You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.
*/

class Solution {
private:
    using Graph = unordered_map<string, unordered_map<string, double>>;

    double dfs(const string& current, const string& target,
               Graph& graph, unordered_set<string>& visited) {
        if(current == target) return 1.0;

        double found = -1.0;
        for(auto& [next, cost] : graph.at(current)){
            if(!visited.count(next)){
                visited.insert(next);
                double result = dfs(next, target, graph, visited);
                visited.erase(next);
                if(result >= 0) {
                    found = cost * result;
                    break;
                }
            }
        }
        // Cache after the loop so we don't mutate the map during iteration
        if(found >= 0) {
            graph[current][target] = found;
            graph[target][current] = 1.0 / found;
        }
        return found;
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        Graph graph;
        for(int i = 0; i < (int)equations.size(); ++i){
            graph[equations[i][0]][equations[i][1]] = values[i];
            graph[equations[i][1]][equations[i][0]] = 1.0 / values[i];
        }

        vector<double> ans;
        ans.reserve(queries.size());
        for(const auto& q : queries){
            if(!graph.count(q[0]) || !graph.count(q[1])){
                ans.push_back(-1.0);
            } else {
                unordered_set<string> visited{q[0]};
                ans.push_back(dfs(q[0], q[1], graph, visited));
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;

    // Test 1: a/b=2.0, b/c=3.0 => a/c=6.0, b/a=0.5, a/e=-1, a/a=1, x/x=-1
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

    // Test 2: a/b=0.5, b/c=1/3, ba/cd not connected
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
