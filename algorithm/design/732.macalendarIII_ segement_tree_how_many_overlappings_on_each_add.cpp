/*
A k-booking happens when k events have some non-empty intersection (i.e., there is some time that is common to all k events.)

You are given some events [startTime, endTime), after each given event, return an integer k representing the maximum k-booking between all the previous events.

Implement the MyCalendarThree class:

MyCalendarThree() Initializes the object.
int book(int startTime, int endTime) Returns an integer k representing the largest integer such that there exists a k-booking in the calendar.
 
*/

class SegementTree{
private:
    struct Node{
        int val = 0; // max overlapping
        int lazy = 0;
        int left = -1;
        int right = -1;
    };
    vector<Node> tree;


public:
    int newNode(){
        tree.emplace_back();
        return  tree.size()-1;
    }
    int update(int root, int l, int r, int start, int end, int delta){
        if(root<0 || root>=(int)tree.size() || r<l) return -1; // invalid root

        if(end<l || r<start) return 0;
        // [startTime, endTime)
        if(start <= l && r <= end){
            tree[root].lazy += delta;
            tree[root].val += delta;
            return tree[root].val;
        }

        // break down
        if(tree[root].left == -1) tree[root].left = newNode();
        if(tree[root].right == -1) tree[root].right = newNode();

        int m = l + (r-l)/2;

        update(tree[root].left, l, m, start, end-1, delta);
        update(tree[root].right, m+1, r, start, end-1, delta);

        tree[root].val = tree[root].lazy +
                        max(tree[tree[root].left].val, tree[tree[root].right].val);

        return tree[root].val;
    }
public:

    SegementTree(){
        tree.reserve(400*60);

    }
};


class MyCalendarThree {
private:
    static constexpr int MIN_TIME = 0;
    static constexpr int MAX_TIME = 1000000000;
    SegementTree tree;
public:
    MyCalendarThree() {
        tree.newNode(); // root
    }

    int book(int startTime, int endTime) {
        return tree.update(0, MIN_TIME, MAX_TIME, startTime, endTime-1, +1);
    }
};
