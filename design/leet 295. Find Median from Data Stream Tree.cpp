class MedianFinder {
private:
    // from small to big
    priority_queue<int, vector<int>, less<int>> top;
    priority_queue<int, vector<int>, greater<int>> bottom;
    /*
        top         bottom
    [ 1 2 3     |    5 6 7 8    ]
    */
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(bottom.empty() || num >= bottom.top()) bottom.push(num);
        else top.push(num);

        if(top.size()+1 < bottom.size()){
            top.push(bottom.top());
            bottom.pop();
        }else if(top.size() > bottom.size()){
            bottom.push(top.top());
            top.pop();
        }
    }
    
    double findMedian() {
        if(top.size()  ==  bottom.size()) return (top.top() + bottom.top()) / 2.0;
        else return bottom.top();
    }
};
