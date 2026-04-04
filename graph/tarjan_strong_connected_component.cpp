#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>

using namespace std;

class TarjanSCC {
    int timer;
    unordered_map<int, int> visitedAt;
    // Discovery times: The order in which a node was first visited.
    unordered_map<int, int> low;
    // Low-link values: The earliest visited node reachable from this node (including itself).
    // when there is a back-edge to an ancestor, low-link value will be updated to that ancestor's usually lower discovery time.
    // this is actually mined to be the smallest visitedAt in the cycle, so all nodes with same low, is one conponent.

    // Key insight:
    //   low < visitedAt  → "I can reach an ancestor, a back edge from me" → inside a cycle, ancestor will collect me
    //   low == visitedAt → scc root: could be one node or the start of the cycle.

    unordered_set<int> currentPath;
    stack<int> path;

    vector<vector<int>> cycles;

    void findSCC(int from, const unordered_map<int, unordered_set<int>>& adj) {
        // Initialize discovery time and low-link value
        ++timer;
        visitedAt[from] = low[from] = timer;
        path.push(from);
        cout<< "visit push " << from << ", visitedAt=" << visitedAt[from] << ", low=" << low[from] << endl;
        currentPath.insert(from);

        // Iterate through successors (if any exist in the map)
        if (adj.count(from)) {
            for (int next : adj.at(from)) {
                // If next is not visited, recurse
                if (visitedAt.find(next) == visitedAt.end()) {
                    findSCC(next, adj);
                    // with dfs, next's low is updated and here we min it back to "from"
                    // thinks about 1->2->3->1, while 3->1 is a back edge and 3 is updated to low[1]
                    // this allows 2 to be updated with low[1] as well.
                    low[from] = min(low[from], low[next]);
                }
                // If next is already visited and on the current path stack,
                // it's a back-edge indicating a cycle
                else if (currentPath.count(next)) {
                    low[from] = min(low[from], visitedAt[next]);
                }
            }
        }

        cout<< "retreat from " << from << ", visitedAt=" << visitedAt[from] << ", low=" << low[from] << endl;
        // If from is a head node, head node means the first node we start a cycle
        // or a head node is just a normal node with out cycle, visitedAt == low.
        // pop the stack and generate an SCC
        if (low[from] == visitedAt[from]) {
            vector<int> currentCycle;
            while (true) {
                int node = path.top();
                cout<< "pop " << node << " from stack for SCC with head " << from << endl;
                path.pop();
                currentPath.erase(node);
                currentCycle.push_back(node);
                if (from == node) break;
            }
            cycles.push_back(currentCycle);
        }
    }

public:
    vector<vector<int>> getSCCs(const unordered_map<int, unordered_set<int>>& adj) {
        timer = 0;
        visitedAt.clear();
        low.clear();
        currentPath.clear();
        while(!path.empty()) path.pop();
        cycles.clear();

        //Run DFS from every unvisited node to handle disconnected components
        for (auto const& [node, neighbors] : adj) {
            if (visitedAt.find(node) == visitedAt.end()) {
                findSCC(node, adj);
            }
        }

        return cycles;
    }
};


int main() {
    TarjanSCC solver;

    // Test Case 1: Two SCCs connected by a bridge
    //
    //   SCC1            SCC2
    //  +----------+    +-------+
    //  | 0 --> 1  |    | 3 --> 4
    //  | ^    |   |    | ^     |
    //  | |    v   |    | |     |
    //  | +--- 2 --|--->| +-----+
    //  +----------+    +-------+
    //
    // Expected SCCs: {0,1,2}, {3,4}

     // How low-link detects SCCs (walkthrough with 0→1→2→0, 2→3→4→3):
    //
    //  Step | Node | visitedAt | Action                  | low update
    //  -----|------|-----------|-------------------------|---------------------------
    //   1   |  0   |    1      | visit, push             | low[0]=1
    //   2   |  1   |    2      | visit, push             | low[1]=2
    //   3   |  2   |    3      | visit, push             | low[2]=3
    //   4   | 2→0  |    —      | 0 on stack (back-edge!) | low[2]=min(3,1)=1
    //   5   |  3   |    4      | visit, push             | low[3]=4
    //   6   |  4   |    5      | visit, push             | low[4]=5
    //   7   | 4→3  |    —      | 3 on stack (back-edge!) | low[4]=min(5,4)=4
    //   8   | ret 3|    —      | from child 4            | low[3]=min(4,4)=4
    //   9   | ret 2|    —      | from child 3            | low[2]=min(1,4)=1
    //  10   | ret 1|    —      | from child 2            | low[1]=min(2,1)=1
    //  11   | ret 0|    —      | from child 1            | low[0]=min(1,1)=1
    //
    //  Node | low | visitedAt | Equal? | Meaning
    //  -----|-----|-----------|--------|----------------------------------------
    //    4  |  4  |     5     |   No   | can reach 3 (ts=4) → not SCC root
    //    3  |  4  |     4     |  Yes   | can't reach before self → SCC root! Pop {4,3}
    //    2  |  1  |     3     |   No   | can reach 0 (ts=1) → not SCC root
    //    1  |  1  |     2     |   No   | can reach 0 → not SCC root
    //    0  |  1  |     1     |  Yes   | can't reach before self → SCC root! Pop {2,1,0}
    //
    unordered_map<int, unordered_set<int>> adj1 = {
        {0, {1}},
        {1, {2}},
        {2, {0, 3}},
        {3, {4}},
        {4, {3, 5}},
        {5, {}}
    };

    // Test Case 2: Disconnected components
    //
    //   SCC1             Singletons
    //  +-----------+    +-----+     +-----+
    //  | 10 --> 20 |    | 100 |---->| 200 |
    //  | ^      |  |    +-----+     +-----+
    //  | +------+  |
    //  +-----------+
    //
    // Expected SCCs: {10,20}, {100}, {200}
    unordered_map<int, unordered_set<int>> adj2 = {
        {10, {20}},
        {20, {10}},
        {100, {200}},
        {200, {}}
    };

    // Test Case 3: Two SCCs and a singleton
    //
    //    SCC1               SCC2          Singleton
    //  +-----------+    +-----------+    +-----+
    //  | 1 --> 2 --|--->| 4 --> 5   |--->| 7   |
    //  | ^    |    |    | ^    |    |    +-----+
    //  | |    v    |    | |    v    |
    //  | +--- 3    |    | +--- 6   |
    //  +-----------+    +-----------+
    //
    // Expected SCCs: {1,2,3}, {4,5,6}, {7}
    unordered_map<int, unordered_set<int>> adj3 = {
        {1, {2}},
        {2, {3, 4}},
        {3, {1}},
        {4, {5}},
        {5, {6}},
        {6, {4, 7}},
        {7, {}}
    };

    auto printSCCs = [](int id, const vector<vector<int>>& result) {
        cout << "--- Test Case " << id << " ---" << endl;
        for (const auto& scc : result) {
            cout << "[ ";
            for (int node : scc) cout << node << " ";
            cout << "]" << endl;
        }
        cout << endl;
    };

    printSCCs(1, solver.getSCCs(adj1));
    // printSCCs(2, solver.getSCCs(adj2));
    // printSCCs(3, solver.getSCCs(adj3));

    return 0;
}
