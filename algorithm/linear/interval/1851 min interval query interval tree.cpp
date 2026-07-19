#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <cassert>
using namespace std;

/*
Interval Tree (augmented BST, CLRS-style)
- BST ordered by interval start (lo)
- Each node augmented with maxEnd = max(hi) in its subtree
- Supports: addInterval, removeInterval, query (min-length interval covering a point)

vs Segment Tree:
- Segment tree: range update, point query, but min() is not reversible → can't remove
- Interval tree: stores each interval as a separate node → can add/remove freely

Complexity (unbalanced BST):
- Insert:  O(h)       h = tree height, O(log n) average, O(n) worst
- Remove:  O(h)
- Query:   O(h + k)   k = number of intervals containing the query point
*/

class IntervalTree{
private:
    struct Node{
        int lo, hi, len;
        int maxEnd;      // max hi in this subtree (for pruning)
        Node* left  = nullptr;
        Node* right = nullptr;
        Node(int lo, int hi)
            : lo(lo), hi(hi), len(hi - lo + 1), maxEnd(hi) {}
    };

    Node* root = nullptr;

    void updateMax(Node* n){
        n->maxEnd = n->hi;
        if(n->left)  n->maxEnd = max(n->maxEnd, n->left->maxEnd);
        if(n->right) n->maxEnd = max(n->maxEnd, n->right->maxEnd);
    }

    Node* insert(Node* n, int lo, int hi){
        if(!n) return new Node(lo, hi);
        if(lo < n->lo || (lo == n->lo && hi < n->hi))
            n->left = insert(n->left, lo, hi);
        else
            n->right = insert(n->right, lo, hi);
        updateMax(n);
        return n;
    }

    Node* findMin(Node* n){
        while(n->left) n = n->left;
        return n;
    }

    Node* remove(Node* n, int lo, int hi){
        if(!n) return nullptr;
        if(lo < n->lo || (lo == n->lo && hi < n->hi)){
            n->left = remove(n->left, lo, hi);
        } else if(lo > n->lo || (lo == n->lo && hi > n->hi)){
            n->right = remove(n->right, lo, hi);
        } else {
            // found the node to remove
            if(!n->left){
                Node* r = n->right;
                delete n;
                return r;
            }
            if(!n->right){
                Node* l = n->left;
                delete n;
                return l;
            }
            // two children: replace with in-order successor
            Node* succ = findMin(n->right);
            n->lo = succ->lo;
            n->hi = succ->hi;
            n->len = succ->len;
            n->right = remove(n->right, succ->lo, succ->hi);
        }
        updateMax(n);
        return n;
    }

    // find min-length interval containing point q
    int query(Node* n, int q){
        if(!n || q > n->maxEnd) return INT_MAX; // prune: nothing in this subtree reaches q

        int result = INT_MAX;

        // check current interval
        if(n->lo <= q && q <= n->hi)
            result = n->len;

        // left subtree: has intervals with lo < n->lo, prune by maxEnd
        result = min(result, query(n->left, q));

        // right subtree: has intervals with lo >= n->lo
        // only worth checking if lo <= q is still possible
        if(n->lo <= q)
            result = min(result, query(n->right, q));

        return result;
    }

    void destroy(Node* n){
        if(!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    void print(Node* n, int depth){
        if(!n) return;
        print(n->left, depth + 1);
        for(int i = 0; i < depth; i++) cout << "  ";
        cout << "[" << n->lo << "," << n->hi << "] len=" << n->len
             << " maxEnd=" << n->maxEnd << endl;
        print(n->right, depth + 1);
    }

public:
    ~IntervalTree(){ destroy(root); }

    void addInterval(int lo, int hi){
        root = insert(root, lo, hi);
    }

    void removeInterval(int lo, int hi){
        root = remove(root, lo, hi);
    }

    // returns min interval length covering q, or -1 if none
    int query(int q){
        int res = query(root, q);
        return res == INT_MAX ? -1 : res;
    }

    void print(){
        print(root, 0);
        cout << "---" << endl;
    }
};

// ── tests ──────────────────────────────────────────────

void test_basic(){
    cout << "=== test_basic ===" << endl;
    // intervals=[[4,5],[5,8],[1,9],[8,10],[1,6]], query=7
    IntervalTree tree;
    tree.addInterval(4, 5);
    tree.addInterval(5, 8);
    tree.addInterval(1, 9);
    tree.addInterval(8, 10);
    tree.addInterval(1, 6);

    // 7 is covered by [5,8](len=4), [1,9](len=9) → min = 4
    assert(tree.query(7) == 4);
    cout << "query(7) = " << tree.query(7) << "  (expected 4)" << endl;

    // 4 is covered by [4,5](2), [1,9](9), [1,6](6) → min = 2
    assert(tree.query(4) == 2);
    cout << "query(4) = " << tree.query(4) << "  (expected 2)" << endl;

    // 10 is covered by [8,10](3) → min = 3
    assert(tree.query(10) == 3);
    cout << "query(10) = " << tree.query(10) << "  (expected 3)" << endl;

    // 11 is not covered → -1
    assert(tree.query(11) == -1);
    cout << "query(11) = " << tree.query(11) << "  (expected -1)" << endl;
}

void test_remove(){
    cout << "\n=== test_remove ===" << endl;
    IntervalTree tree;
    tree.addInterval(4, 5);
    tree.addInterval(5, 8);
    tree.addInterval(1, 9);
    tree.addInterval(8, 10);
    tree.addInterval(1, 6);

    cout << "before remove [5,8]:" << endl;
    cout << "query(7) = " << tree.query(7) << "  (expected 4)" << endl;
    assert(tree.query(7) == 4);

    // remove [5,8] → now 7 covered only by [1,9](9) → min = 9
    tree.removeInterval(5, 8);
    cout << "after remove [5,8]:" << endl;
    cout << "query(7) = " << tree.query(7) << "  (expected 9)" << endl;
    assert(tree.query(7) == 9);

    // remove [1,9] → now 7 not covered → -1
    tree.removeInterval(1, 9);
    cout << "after remove [1,9]:" << endl;
    cout << "query(7) = " << tree.query(7) << "  (expected -1)" << endl;
    assert(tree.query(7) == -1);

    // 4 still covered by [4,5](2), [1,6](6) → min = 2
    cout << "query(4) = " << tree.query(4) << "  (expected 2)" << endl;
    assert(tree.query(4) == 2);
}

void test_dynamic_update(){
    cout << "\n=== test_dynamic_update ===" << endl;
    IntervalTree tree;
    tree.addInterval(1, 9);

    cout << "query(5) = " << tree.query(5) << "  (expected 9)" << endl;
    assert(tree.query(5) == 9);

    // "update" [1,9] → [1,5]: remove old, add new
    tree.removeInterval(1, 9);
    tree.addInterval(1, 5);
    cout << "after update [1,9]->[1,5]:" << endl;
    cout << "query(5) = " << tree.query(5) << "  (expected 5)" << endl;
    assert(tree.query(5) == 5);
    cout << "query(7) = " << tree.query(7) << "  (expected -1)" << endl;
    assert(tree.query(7) == -1);
}

void test_leetcode_example(){
    cout << "\n=== test_leetcode_example ===" << endl;
    // intervals = [[1,3],[2,3],[3,7],[6,6]], queries = [2,3,1,7,6,8]
    IntervalTree tree;
    tree.addInterval(1, 3);
    tree.addInterval(2, 3);
    tree.addInterval(3, 7);
    tree.addInterval(6, 6);

    int expected[] = {2, 2, 3, 5, 1, -1};
    int queries[]  = {2, 3, 1, 7, 6, 8};
    for(int i = 0; i < 6; i++){
        int res = tree.query(queries[i]);
        cout << "query(" << queries[i] << ") = " << res
             << "  (expected " << expected[i] << ")" << endl;
        assert(res == expected[i]);
    }
}

int main(){
    test_basic();
    test_remove();
    test_dynamic_update();
    test_leetcode_example();
    cout << "\nAll tests passed!" << endl;
    return 0;
}
