class Solution {
  
  /*
  Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

 

Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
Example 2:

Input: arr = [2,3,5], target = 10
Output: 5
Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
  
  */
public:
    int findBestValue(vector<int>& arr, int target) 
    {
        vector<int> diagram(arr);
        sort(diagram.begin(), diagram.end());
        size_t size = diagram.size();
        
        int sum = 0;
        int current = 0;
        int total = 0;
        int restSize = diagram.size();
        
        while(current<size)
        {
            if(target <= restSize*diagram[current] + sum) break;
            
            sum+= diagram[current];
            ++current;
            --restSize;
        }
        
        if(restSize == 0) return diagram.back();
        //here to find value where : value * restSize + sum = target
        target -= sum;
        //cout<< target<<" / "<< restSize<<endl;
        double seed  = (double)target/restSize;
        
        return seed+0.49;//>0.5 will be +1, more close to target
    }
};
