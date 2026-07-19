/*
There are n children standing in a line. 
Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:

Input: ratings = [4,3,5]

Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:

Input: ratings = [2,3,3]

Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

Constraints:

1 <= ratings.length <= 20,000
0 <= ratings[i] <= 20,000
[2,3,3]

idea:
    if r_i-1 > r_i < r_i+1 -> i will get one

    we can assum current one is candy = 0; 
    go next: 
        ifr_i < r_i+1: ++candy 
        else --candy

        minCandy -> the base line : (-minCandy+1)
    
    all candy+= (-minCandy+1)

    so total is sum(candy + n*base)
    

    [4,3,5]
     0 -1 0]
     base line is  -(-1) + 1 = 2
     2 1 2 

    [2,3,3]
     0 1 0
     1 2 1

    not working:
     [1,3,2, 2, 1]
      0 1 0 -1 -2
      3 4 3  2  1

      however: 
      1 3 2 2  1 


solution:
    left pass raising constraints
    right pass falling contraints with max current


*/
#include<vector>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        const int n = ratings.size();
        vector<int> candies(n, 1);

        // left to right: enforce rising constraint
        for(int i=1; i<n; ++i){
            if(ratings[i-1] < ratings[i])
                candies[i] = candies[i-1] + 1;
        }

        // right to left: enforce falling constraint
        for(int i=n-2; i>=0; --i){
            if(ratings[i] > ratings[i+1])
                // candies[i] maybe already bigger for the left constrains
                candies[i] = max(candies[i], candies[i+1] + 1);
        }

        int sum = 0;
        for(int c : candies) sum += c;
        return sum;
    }
};
