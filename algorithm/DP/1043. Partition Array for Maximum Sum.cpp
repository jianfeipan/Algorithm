/*
1043. Partition Array for Maximum Sum
Medium

Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

 

Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
Example 2:

Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
Example 3:

Input: arr = [1], k = 1
Output: 1
 

Constraints:

1 <= arr.length <= 500
0 <= arr[i] <= 109
1 <= k <= arr.length

*/

class Solution {


/*
Fact: 
    1 32 bit int garenteed
    2 subarray contiguous: same order
    3 k is max lenght of the subarray: all k elements take the max of subarray
    4 need to find largest sum after partitioning

Idea:
    1 eg: [1,15,7,9,2,5,10], k = 3
           if no k limit, I take the max * k 
           if k = 1: max_sum = sum

           now k=3, I need to make sure the subarray has length 3 when I have a big element like 15 then 10, then it's 9
           --> start with 15, let 15 take the smaller neighber to the same subarray, do this 2 times, we have [1 15 7]
                then with 10 the max left: take 5 and 2: [2, 5, 10]
                left 9

        eg: [1,4,1,5,7,3,6,1,9,9,3], k = 4

            --> start with 9, take 3 neighbors: [3 6 1 9 ] and [9 3]  sum 54
                with 7 [ 4 1 5 7] sum 28
                with 1 sum 1
                sum(83) -> correct


        eg: arr =[10,9,3,2] k =2
            --> start with 10, [10 9]
                then 3 [3, 2]
                = sum 26

                !!! however, we can do [10, 9, 9, 2] which makes 30!

    diea2 : this is a typical dynamic programming problem, you cannot just rely on greedy, because you may miss the global optimal, 
            the only way is to have all the possibilities.

            take first element as partition 1, see the max value from the rest of the array
            then take [0 1 ] as partition, seet hte max of the rest
            ...
            then take [0, 1, 2 ...k] see the rest

            O(N*K)

            




*/
public:
    int maxSumAfterPartitioning_idea1_failed_greedy(vector<int>& arr, int k) {
        if(k>=arr.size()) return arr.size()*(*std::max_element(arr.begin(), arr.end()));

        unordered_set<int> taken;
        int sum = 0;
        while(taken.size()<arr.size()){

            //find max
            int maxIndex = 0;
            int maxValue=0;
            for(int i=0; i<arr.size(); ++i){
                if(!taken.contains(i)){
                    if(maxValue<arr[i]){
                        maxValue = arr[i];
                        maxIndex=i;
                    }
                }
            }
            // std::cout<<"For max  index="<<maxIndex<<" value"<<arr[maxIndex]<<std::endl;

            //take smaller numbers to that array
            int arrayStart = maxIndex;
            int arrayEnd = maxIndex;

            taken.insert(maxIndex);
            for(int i=1; i<k; ++i){
                int left = arrayStart-1;
                int right = arrayEnd+1;

                bool leftValid = left>=0 && !taken.contains(left);
                bool rightValid = right<arr.size() && !taken.contains(right);
                
                if(leftValid&&rightValid){
                    if(arr[left] <= arr[right]){
                        //take left
                        arrayStart=left;
                        taken.insert(left);
                        // std::cout<<"take left"<<arr[left]<<std::endl;
                    }
                    else{
                        //take right
                        arrayEnd = right;
                        taken.insert(right);
                        // std::cout<<"take right"<<arr[right]<<std::endl;
                    }
                }
                else{
                    if(leftValid){
                        //take left
                        arrayStart=left;
                        taken.insert(left);
                        // std::cout<<"take left"<<arr[left]<<std::endl;
                    }
                    else if(rightValid){
                        //take right
                        arrayEnd = right;
                        taken.insert(right);
                        // std::cout<<"take right"<<arr[right]<<std::endl;
                    }else{
                        break;
                    }
                }
                
            }

            //compute sum

            sum= sum + (arrayEnd - arrayStart + 1 ) * maxValue;
            //failed with [10,9,3,2] k = 2

        }

        return sum;
    }



       int maxSumAfterPartitioning(vector<int>& arr, int k) {
        
        return maxSumAfterPartitioning_dp(0, arr, k);
    }



    private:

        unordered_map<int, int> cache; 
        int maxSumAfterPartitioning_dp(int from, const vector<int>& arr, int k) {
            
            //boundry condition
            if(from==arr.size()) return 0;
            
            auto it = cache.find(from);

            if(it != cache.end()) return it->second;

            const int partitionStart = from;
            const int maxPartitionEnd = std::min(from+k-1, (int)arr.size()-1);
            int maxSum = 0;
            int maxElement = 0;
            
            for(int partitionEnd = from; partitionEnd<= maxPartitionEnd; ++partitionEnd){
                maxElement = std::max(maxElement, arr[partitionEnd]);

                int current = maxElement*(partitionEnd - from+1) + maxSumAfterPartitioning_dp(partitionEnd+1, arr, k);

                maxSum = std::max(maxSum, current);
            }

            cache[from] = maxSum;

            return maxSum;
        }


    
};
