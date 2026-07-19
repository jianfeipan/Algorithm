/*
BAD question

Given the array queries of positive integers between 1 and m, you have to process all queries[i] (from i=0 to i=queries.length-1) according to the following rules:

In the beginning, you have the permutation P=[1,2,3,...,m].
For the current i, find the position of queries[i] in the permutation P (indexing from 0) and then move this at the beginning of the permutation P. Notice that the position of queries[i] in P is the result for queries[i].
Return an array containing the result for the given queries.

 

Example 1:

Input: queries = [3,1,2,1], m = 5
Output: [2,1,2,1] 
Explanation: The queries are processed as follow: 
For i=0: queries[i]=3, P=[1,2,3,4,5], position of 3 in P is 2, then we move 3 to the beginning of P resulting in P=[3,1,2,4,5]. 
For i=1: queries[i]=1, P=[3,1,2,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,3,2,4,5]. 
For i=2: queries[i]=2, P=[1,3,2,4,5], position of 2 in P is 2, then we move 2 to the beginning of P resulting in P=[2,1,3,4,5]. 
For i=3: queries[i]=1, P=[2,1,3,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,2,3,4,5]. 
Therefore, the array containing the result is [2,1,2,1].  
*/


class Solution {
/*
idea:
    do everything as it asks to..... 

*/

public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> pos(m);
        for(int i = 0; i<m; ++i)
        {
            pos[i] = i;
        }

        vector<int> res(queries.size(), 0);
        for(int i = 0; i<queries.size(); ++i)
        {
            int query = queries[i];
            int queryPos = pos[query-1];

            res[i] = queryPos;
            //move query to position 0, and move all position < queryPos to right (++1)
            for(int j = 0; j<pos.size(); ++j)
            {
                if(pos[j]== queryPos) pos[j] = 0;
                else if(pos[j]<queryPos) ++pos[j];
            }

        }

        return res;
    }
};
