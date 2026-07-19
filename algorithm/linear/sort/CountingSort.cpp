/*

or simplicity, consider the data in the range 0 to 9. 
Input data: 1, 4, 1, 2, 7, 5, 2
  1) Take a count array to store the count of each unique object.
  Index:     0  1  2  3  4  5  6  7  8  9
  Count:     0  2  2  0   1  1  0  1  0  0

  2) Modify the count array such that each element at each index 
  stores the sum of previous counts. 
  Index:     0  1  2  3  4  5  6  7  8  9
  Count:     0  2  4  4  5  6  6  7  7  7

The modified count array indicates the position of each object in 
the output sequence.

*/

void countingSort(vector<int> & nums)//nums range = 0 - RANGE
{
    vector<int> sorted(nums.size(), 0);
    
    vector<int> count(RANGE, 0);
    for(auto num : nums) ++count[num];
    
    for(size_t i = 1; i<RANGE; ++i)
    {
        count[i]+=count[i-1];//cumulated sum
    }
    
    for(auto num : nums)
    {
        sorted[count[num] - 1] = num;//cumulated count value is the position of the element index = count[num] - 1
        --count[num];
    }
    nums = sorted;
}
