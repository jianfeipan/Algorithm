class KthLargest {
  
  
  
  
  /*
  
  main Idea is a min heap with size k, every time you just insert then pop it until size k, so the top i the heap will be the k - est big
  
  you don't need to store all the elements
  
  Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers nums.
int add(int val) Appends the integer val to the stream and returns the element representing the kth largest element in the stream.
  
  */
public:
    priority_queue<int,vector<int>,greater<int>>minHeap;
    int k;
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
        for(int i=0;i<nums.size();i++)
        {
            if(i<k)
                minHeap.push(nums[i]);
            else if(minHeap.top()<nums[i])
            {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
    }
    
    int add(int val) {
        
        if(minHeap.size()<k)
            minHeap.push(val);
        else if(minHeap.top()<val)
        {
                minHeap.pop();
                minHeap.push(val);
        }
        return minHeap.top();
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
