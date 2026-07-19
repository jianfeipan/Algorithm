/*
problem : given a array, find the k th smallest element

the idea is like quick sort, but we use partitions to count not for sorting.
    pick a random value front the array, do the partition : [left] pivot [right]
    if left.size  == k-1 : pivot is the k th smallest value
    else if left.size < k-1 do the same on the right
    else do the same on the left
*/

int select(vector<int> nums, int k)
{
   
    return quickSelect(nums, 0, nums.size()-1, k);
}

int quickSelect(vector<int> & nums, int from, int to, int k)
{
    if(from == to) 
    auto pivotIndex = random()%(to - from +1);
    
    swap(nums, pivotIndex, to);
    
    auto pivot = nums[to+1];
    int leftLimit = -1;
    for(size_t i = from; i<=to; ++i)
    {
        if(nums[i] < pivot) 
        {
            swap(nums, i, leftLimit+1)
            ++leftLimit;
        }
    }
    
    swap(nums, to+1, leftLimit+1);
    
    // partitions is [from, leftLimit] [ pivot, to+1]
    if(leftLimit - from +1 == k - 1)
        return pivot;
    else if(leftLimit - from +1 < k - 1)//int right partition will be the k -  (leftLimit - from +1) th
        return quickSelect(nums, leftLimit +1, to, k - (leftLimit - from +1));
    else
        return quickSelect(nums, from, leftLimit, k);
}  
    


