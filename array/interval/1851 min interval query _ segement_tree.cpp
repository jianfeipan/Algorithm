#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
using namespace std;

class Solution_sort_and_minHeap {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // sort intervals
        sort(intervals.begin(), intervals.end());

        // sort queries
        const auto n = queries.size();
        vector<int> sortedQuery(n);
        for(int i=0; i<n; ++i) sortedQuery[i] = i;
        sort(sortedQuery.begin(), sortedQuery.end(), [&](int idx1, int idx2){
            return queries[idx1] < queries[idx2];
        });

        vector<int> ans(n);

        using Len = int;
        using End = int;
        using Node = pair<Len, End>;
        using MinHeap = priority_queue<Node, vector<Node>, greater<Node>>;
        MinHeap minIntervals;

        auto intervalIt = intervals.begin();

        for(auto qIdx : sortedQuery){
            auto query = queries[qIdx];
            int minimalInterval = -1;
            {
                // push intervals start before the query into a miinHeap on len and end date
                while(intervalIt!=intervals.end() && intervalIt->at(0) <= query){
                    const auto len = intervalIt->at(1) - intervalIt->at(0) + 1; // [l,r] inclusive
                    minIntervals.push({len, intervalIt->at(1)});
                    ++intervalIt;
                }

                // pop intervals end bfore the query
                while(!minIntervals.empty() && minIntervals.top().second < query){
                    minIntervals.pop();
                }
                if(!minIntervals.empty()) minimalInterval = minIntervals.top().first;
            }
            ans[qIdx] = minimalInterval;
        }

        return ans;

    }
};

class Solution {
private:
    class SegementTree{
    private:
        constexpr static int MIN = 0;
        constexpr static int MAX = 100000000;
        struct Node{
            int val=INT_MAX;
            int left=-1;
            int right=-1;
        };
        vector<Node> tree;

        int newNode(){
            tree.emplace_back();
            return tree.size() - 1;
        }

        void update(int root, int l, int r, int start, int end, int val){
            if(root == -1) return; // invalide node
            if(end < l || r < start || r < l) return; //no overlapping

            //cout<< root<<": ["<< l <<","<< r << "]"<<endl;

            if(start <= l && r <= end){
                tree[root].val = min(tree[root].val, val);
                return;
            }

            int m = l + (r-l)/2;
            if(tree[root].left == -1) tree[root].left = newNode();
            if(tree[root].right == -1) tree[root].right = newNode();

            update(tree[root].left, l, m, start, end, val);
            update(tree[root].right, m+1, r, start, end, val);
            // [l, m] and [m+1, r] instead of [l. m-1] because we are dong floor of  (r-l)/2
            // so the m is biased toward left!!!
        }

        int query(int root, int l, int r, int q){
            if(root == -1) return INT_MAX;
            if(q < l || r < q) return INT_MAX;
            if(l == r) return tree[root].val;

            int m = l + (r-l)/2;
            int child;
            if(q<=m) child = query(tree[root].left, l, m, q);
            else child = query(tree[root].right, m+1, r, q);
            return min(tree[root].val, child);
        }

        void print(int root){
            cout<<root<<":"<<tree[root].val;
            if(tree[root].left != -1){
                cout<< " { " ;
                print(tree[root].left);
                cout<< " , " ;
                print(tree[root].right);
                cout<< " } " ;
            }
        }

    public:
        SegementTree(){
            tree.reserve(MAX*2);
            newNode(); // make root
        }

        void addInterval(int start, int end){
            if(end <start) return; // invalid input
            int len = end - start +1; // [l,r] inclusive interval
            update(0, MIN, MAX, start, end, len);
        }

        int minLenQuery(int q){
            int res = query(0, MIN, MAX, q);
            return res == INT_MAX ? -1 : res;
        }

        void printTree(){
            print(0);
        }
    };

public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        SegementTree tree;
        for(const auto& interval : intervals) tree.addInterval(interval.at(0), interval.at(1));

        vector<int> ans; ans.reserve(queries.size());
        for(const auto query : queries) ans.push_back(tree.minLenQuery(query));

        //tree.printTree();
        return ans;
    }
};


int main() {
    Solution sol;

    // 测试用例 1：LeetCode 示例
    // intervals = [[1,4],[2,4],[3,6],[2,8]], queries = [2,3,4,5]
    // 期望输出: [3,3,3,4]
    {
        vector<vector<int>> intervals = {{1,4},{2,4},{3,6},{2,8}};
        vector<int> queries = {2,3,4,5};
        vector<int> result = sol.minInterval(intervals, queries);
        assert((result == vector<int>{3,3,3,4}));
    }

    // 测试用例 2：LeetCode 示例
    // intervals = [[2,3],[2,5],[1,8],[20,25]], queries = [2,19,5,22]
    // 期望输出: [2,−1,4,6]
    {
        vector<vector<int>> intervals = {{2,3},{2,5},{1,8},{20,25}};
        vector<int> queries = {2,19,5,22};
        vector<int> result = sol.minInterval(intervals, queries);
        assert((result == vector<int>{2,-1,4,6}));
    }

    // 测试用例 3：查询点不在任何区间内
    {
        vector<vector<int>> intervals = {{1,2},{3,4}};
        vector<int> queries = {5};
        vector<int> result = sol.minInterval(intervals, queries);
        assert((result == vector<int>{-1}));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
