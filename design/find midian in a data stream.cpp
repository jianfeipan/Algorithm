/*
The median is the middle value in a sorted list of integers. For lists of even length, there is no middle value, so the median is the mean of the two middle values.

For example:

For arr = [1,2,3], the median is 2.
For arr = [1,2], the median is (1 + 2) / 2 = 1.5
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far.
Example 1:

Input:
["MedianFinder", "addNum", "1", "findMedian", "addNum", "3" "findMedian", "addNum", "2", "findMedian"]

Output:
[null, null, 1.0, null, 2.0, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.findMedian(); // return 1.0
medianFinder.addNum(3);    // arr = [1, 3]
medianFinder.findMedian(); // return 2.0
medianFinder.addNum(2);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
Constraints:

-100,000 <= num <= 100,000
findMedian will only be called after adding at least one integer to the data structure.


*/
struct Greater{
    bool operator()(int l, int r){ return l>r;}
};
struct Smaller{
    bool operator()(int l, int r){ return l<r;}

};


class MedianFinder {

 /*
 solution1: push all nums to a vector when find do sort
 add: O(1)
 find: O(NlogN)

 solution2: we maintain two heaps: 
 minHeap and maxHeap, minHeap has all the big numbers, max for all the small ones,
 so the find will be just the top of minHeap and maxHeap
add: O(logN)
find: O(1)
 */   
private:
    priority_queue<int, vector<int>, Greater> minHeap;
    priority_queue<int, vector<int>, Smaller> maxHeap;

public:
    MedianFinder() {

        // minHeap.push(INT_MAX);
        // maxHeap.push(INT_MIN);
    }
    
    void addNum(int num) {
        if(maxHeap.empty() && minHeap.empty()){
            maxHeap.push(num);
        }else{
            if(num <= maxHeap.top()){ // num is smaller section
                maxHeap.push(num);
            }else{
                minHeap.push(num);
            }
        }
        
        //rebalance 
        if(maxHeap.size() > minHeap.size()+1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }else if(maxHeap.size() + 1 < minHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if(maxHeap.size() == minHeap.size()){
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        else if(maxHeap.size() > minHeap.size()){
            return maxHeap.top();
        }else{
            return minHeap.top();
        }
    }
};



#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxHeap; // smaller half (max heap)
    priority_queue<int, vector<int>, greater<int>> minHeap; // bigger half (min heap)
public:
    MedianFinder() {

    }

    void addNum(int num) {
        maxHeap.push(num);
        // move the largest of the smaller half to the bigger half
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        // rebalance: maxHeap should always have >= elements than minHeap
        if(minHeap.size() > maxHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if(maxHeap.size() == minHeap.size()){
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};

int main() {
    // Test 1: LeetCode example [1, 2, 3]
    {
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        assert(mf.findMedian() == 1.5);
        mf.addNum(3);
        assert(mf.findMedian() == 2.0);
        cout << "Test 1 passed: [1,2,3]" << endl;
    }

    // Test 2: single element
    {
        MedianFinder mf;
        mf.addNum(5);
        assert(mf.findMedian() == 5.0);
        cout << "Test 2 passed: single element" << endl;
    }

    // Test 3: two elements
    {
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        assert(mf.findMedian() == 1.5);
        cout << "Test 3 passed: two elements" << endl;
    }

    // Test 4: negative numbers
    {
        MedianFinder mf;
        mf.addNum(-1);
        mf.addNum(-2);
        mf.addNum(-3);
        assert(mf.findMedian() == -2.0);
        cout << "Test 4 passed: negative numbers" << endl;
    }

    // Test 5: duplicates
    {
        MedianFinder mf;
        mf.addNum(5);
        mf.addNum(5);
        mf.addNum(5);
        mf.addNum(5);
        assert(mf.findMedian() == 5.0);
        cout << "Test 5 passed: duplicates" << endl;
    }

    // Test 6: descending order
    {
        MedianFinder mf;
        mf.addNum(6);
        assert(mf.findMedian() == 6.0);
        mf.addNum(5);
        assert(mf.findMedian() == 5.5);
        mf.addNum(4);
        assert(mf.findMedian() == 5.0);
        mf.addNum(3);
        assert(mf.findMedian() == 4.5);
        mf.addNum(2);
        assert(mf.findMedian() == 4.0);
        cout << "Test 6 passed: descending order" << endl;
    }

    cout << "All tests passed!" << endl;
    return 0;
}

