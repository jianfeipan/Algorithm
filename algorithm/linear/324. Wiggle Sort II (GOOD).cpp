class Solution {
public:
    void wiggleSort_max_heap(vector<int>& nums) {//O(nlogn)
       int n=nums.size();
       //max heap
       priority_queue<int>pq;
       for(int x:nums) pq.push(x);
       //put the top large values in odd positions
       //ex-> [1,5,1,1,6,4]------>[_6_5_4_]
       int i=1;
       while(pq.size() and i<n){
           nums[i]=pq.top();
           pq.pop();
           i+=2;
       }
       //put remaining values in even position
       //[1,6,5,1,4,1] 
       int j=0;
       while(pq.size() and j<n){
           nums[j]=pq.top();
           pq.pop();
           j+=2;
       }
    }

    void wiggleSort(vector<int>& nums) {//sort O(nlogn)

        vector<int> sorted(nums);

        std::sort(sorted.begin(), sorted.end(), std::greater<int>());
        int j = 0;
        for(int i = 1; i<nums.size(); i+=2, ++j) //odd positions
        {
            nums[i] = sorted[j];
        }

        for(int i = 0; i<nums.size(); i+=2, ++j) //even
        {
            nums[i] = sorted[j];
        }

    }
};
