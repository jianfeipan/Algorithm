class Solution {
public:
    /**
     * @param nums: an array containing n + 1 integers which is between 1 and n
     * @return: the duplicate one
     */
    int findDuplicate(vector<int>& nums)
    {
        int i = 0;
        while(nums[i]!=-1)// nums[i] visited: i duplicated
        {
            int next = nums[i];
            nums[i] = -1;//mark and we need to use this index, because we lost it
            i = next;//use the index that we just earased
        }
        return i;
    }



}//;633 · Find the Duplicate Number
