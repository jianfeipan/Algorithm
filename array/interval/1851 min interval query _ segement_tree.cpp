#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <iostream>
using namespace std;

/*
intervals = [[1,3],[2,3],[3,7],[6,6]],
queries = [2,3,1,7,6,8]

2: [1,3],[2,3]
3: [1,3],[2,3],[3,7]
1: [1,3]
7: [3,7]
6: [3,7][6,6]
8:..
BF: O(I*Q)
for each query Q, check all intervals I: Q*I

can we only scan I once?
sorting -> Q and I by start

look at the timeline:

[ [ q1[ [ [q2 [ [ [q3 [ [

q1 can only be covered by I  "start before q1", -> candidates -> push
q1 can only be covered by I  "end after q1", -> filter -> pop
then we need the order of length (end - start+1) -> target -> minHeap (logI)

*/



// the solution with minHeap is not dynamic: when we update the intervals, we need to redo the whole coputations
// if we want to cover the dynamic case: segement tree is the solution

// Dynamic segment tree: no coordinate compression needed.
// Works directly on the real value range [lo, hi].
// Nodes are created on demand, so even range [0, 1e9] is fine — only O(n*logR) nodes.
class DynamicSegmentTree{
private:
    struct Node{
        int val   = INT_MAX; // min value covering this node's entire range
        int left  = -1;      // child index, -1 = not created
        int right = -1;
    };

    vector<Node> nodes;
    int lo, hi;

    int newNode(){
        nodes.push_back({});
        return nodes.size() - 1;
    }

    // no lazy: when [start,end] fully covers [l,r], store value here and stop
    void update(int root, int start, int end, int value, int l, int r){
        if(end < l || r < start) return;
        if(start <= l && r <= end){
            nodes[root].val = min(nodes[root].val, value);
            return;
        }
        int m = l + (r - l) / 2;
        if(nodes[root].left  == -1) nodes[root].left  = newNode();
        if(nodes[root].right == -1) nodes[root].right = newNode();
        update(nodes[root].left,  start, end, value, l, m);
        update(nodes[root].right, start, end, value, m+1, r);
    }

    // collect the min of all node values along root-to-leaf path
    int query(int root, int q, int l, int r, int currentMin){
        if(root == -1) return currentMin;
        currentMin = min(currentMin, nodes[root].val);
        if(l == r) return currentMin;
        int m = l + (r - l) / 2;
        if(q <= m) return query(nodes[root].left,  q, l, m, currentMin);
        else       return query(nodes[root].right, q, m+1, r, currentMin);
    }

public:
    DynamicSegmentTree(int lo, int hi) : lo(lo), hi(hi) {
        newNode(); // root = index 0
    }

    // range update: mark [start,end] with min(value)
    void addInterval(int start, int end, int value){
        if(start > end) return;
        update(0, start, end, value, lo, hi);
    }

    // point query: returns min interval length covering q, or -1
    int query(int q){
        if(q < lo || q > hi) return -1;
        int res = query(0, q, lo, hi, INT_MAX);
        return res == INT_MAX ? -1 : res;
    }
};

class Solution{
public:
    // build tree from intervals only — queries are NOT needed upfront
    DynamicSegmentTree buildTree(vector<vector<int>>& intervals){
        int lo = INT_MAX, hi = INT_MIN;
        for(const auto& iv : intervals){
            lo = min(lo, iv[0]);
            hi = max(hi, iv[1]);
        }
        DynamicSegmentTree tree(lo, hi);
        for(const auto& iv : intervals){
            tree.addInterval(iv[0], iv[1], iv[1] - iv[0] + 1);
        }
        return tree;
    }

    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        auto tree = buildTree(intervals);
        vector<int> ans;
        for(int q : queries){
            ans.push_back(tree.query(q));
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> intervals = {{4,5},{5,8},{1,9},{8,10},{1,6}};
    vector<int> queries = {7};

    Solution sol;

    // build once from intervals — no queries needed at build time
    auto tree = sol.buildTree(intervals);

    // query anything at any time
    for(int q : queries){
        cout << "query " << q << " -> " << tree.query(q) << endl;
    }
    // expected: query 7 -> 4 (interval [5,8] has size 4)

    // can add more intervals dynamically and query new points
    tree.addInterval(6, 7, 2); // new interval [6,7], length 2
    cout << "query 7 after adding [6,7] -> " << tree.query(7) << endl;
    // expected: 2

    return 0;
}
