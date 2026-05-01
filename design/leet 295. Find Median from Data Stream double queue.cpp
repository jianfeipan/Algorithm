class MedianFinder {
private:
    priority_queue<int> maxHeap; // upper part
    priority_queue<int, vector<int>, greater<int>> minHeap; // lower part

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());maxHeap.pop();

        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        auto upper = maxHeap.size();
        auto lower = minHeap.size();

        if((upper+lower)%2 ==0) return (maxHeap.top() + minHeap.top()) / 2.0;
        else return maxHeap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
