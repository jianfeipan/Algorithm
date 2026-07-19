class Solution {
public:
    /**
     * @param candies: a list of integers
     * @return: return a integer
     
     
     Description
Given an integer array with even length, where different numbers in this array represent different kinds of candies. Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. Returns the maximum number of candy types available to sister.

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].

Example
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 


[]
[1]
[1,2,3]
[1,1,2,2,3,3]
[505,8,951,606,475,401,451,903,618,772,760,475,310,417,728,972,646,794,648,315,353,698,55,88,503,798,297,139,879,99,917,38,554,747,561,175,956,373,672,941,267,680,89,902,127,428,545,914,586,349,339,152,185,340,220,547,648,364,939,641,212,422,621,512,338,826,887,813,125,955,4,874,804,868,231,939,114,237,298,606,199,965,972,141,676,90,369,289,628,12,588,236,254,370,920,298,566,888,316,173]

     
     
     */
    int distributeCandies(vector<int> &candies) {
        // How many types has more than one candies
        unordered_set<int> candiesByType;
        
        for(int candy : candies)
        {
            candiesByType.insert(candy);
        }

        if(candiesByType.size() > candies.size() / 2)
        {
            return candies.size()/2;
        }
        else{
            return candiesByType.size();
        }
        
    }
};
