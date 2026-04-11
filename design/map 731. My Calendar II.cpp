/*
731. My Calendar II
You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a triple booking.

A triple booking happens when three events have some non-empty intersection (i.e., some moment is common to all the three events.).

The event can be represented as a pair of integers startTime and endTime that represents a booking on the half-open interval [startTime, endTime), the range of real numbers x such that startTime <= x < endTime.

Implement the MyCalendarTwo class:

MyCalendarTwo() Initializes the calendar object.
boolean book(int startTime, int endTime) Returns true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.
*/
class MyCalendarTwo_sweapline {
private:
    map<int, int> sweapLine;

public:
    MyCalendarTwo_sweapline() {
        
    }
    
    bool book(int startTime, int endTime) {
        ++sweapLine[startTime];
        --sweapLine[endTime];

        int overlapping = 0;
        for(const auto& [t, count] : sweapLine){
            overlapping+=count;
            if(overlapping==3){
                --sweapLine[startTime];
                ++sweapLine[endTime];
                return false;
            }
        }

        return true;
    }
};


class MyCalendarTwo {
private:
    struct Node {
        int maxVal = 0;   // maximum overlap in this segment
        int lazy = 0;    // increment applied uniformly to whole segment
        int left = -1;
        int right = -1;
    };

    vector<Node> tree;
    static constexpr int MIN_TIME = 0;
    static constexpr int MAX_TIME = 1000000000;

    int newNode() {
        tree.push_back(Node());
        return (int)tree.size() - 1;
    }

    void ensureChildren(int idx) {
        if (tree[idx].left == -1) tree[idx].left = newNode();
        if (tree[idx].right == -1) tree[idx].right = newNode();
    }

    void update(int idx, int l, int r, int ql, int qr, int delta) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            tree[idx].lazy += delta;
            tree[idx].maxVal += delta;
            return;
        }

        ensureChildren(idx);
        int mid = l + (r - l) / 2;

        update(tree[idx].left, l, mid, ql, qr, delta);
        update(tree[idx].right, mid + 1, r, ql, qr, delta);

        tree[idx].maxVal = tree[idx].lazy +
                           max(tree[tree[idx].left].maxVal,
                               tree[tree[idx].right].maxVal);
        
    }

    int query(int idx, int l, int r, int ql, int qr) const {
        if (idx == -1 || qr < l || r < ql) return 0;

        if (ql <= l && r <= qr) {
            return tree[idx].maxVal;
        }

        int mid = l + (r - l) / 2;

        int leftMax = query(tree[idx].left, l, mid, ql, qr);
        int rightMax = query(tree[idx].right, mid + 1, r, ql, qr);


        return tree[idx].maxVal;
    }

public:
    MyCalendarTwo() {
        tree.reserve(400000);
        newNode(); // root = 0
    }
    
    bool book(int startTime, int endTime) {
        int l = startTime;
        int r = endTime - 1;

        update(0, MIN_TIME, MAX_TIME, l, r, 1);

        if (query(0, MIN_TIME, MAX_TIME, l, r) >= 3) {
            update(0, MIN_TIME, MAX_TIME, l, r, -1);
            return false;
        }

        return true;
    }

    int rangeMax(int startTime, int endTime) const {
        return query(0, MIN_TIME, MAX_TIME, startTime, endTime - 1);
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */
