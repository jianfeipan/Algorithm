class KthLargest {
public:
    priority_queue<int,vector<int>,greater<int>>minHeap;// by default it's max heap with a less
    int k;
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
        for(int i=0;i<nums.size();i++)
        {
            add(nums[i]);
        }
    }
    
    int add(int val) {
        
        if(minHeap.size()<k)
            minHeap.push(val);
        else if(minHeap.top()<val) //val is biger, so pop the smallest one, and push this new
        {
                minHeap.pop();
                minHeap.push(val);//push will do a heapify and the top will be the smallest agine
        }
        return minHeap.top();
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
