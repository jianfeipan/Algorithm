/*
1442. Count Triplets That Can Form Two Arrays of Equal XOR
Medium
1.3K
57
Companies
Given an array of integers arr.

We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:

a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

 

Example 1:

Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
Example 2:

Input: arr = [1,1,1,1,1]
Output: 10
*/

class Solution {

    /*
    fact:
        (a^b^c) ^a = b^c

        0 1 ..., i,..., j - 1, j, ..., k, ...n
                     a            b
        
        
    idea:
        1 brutforce : let i start from 0, find j and k
        2 

    */
public:
    int countTriplets_brut_force(vector<int>& arr) {//O(n^4)
        if(arr.size() <2) return 0;
        int count = 0;
        for(int i = 0; i<=arr.size()-2; ++i)
        {
            for(int j = i+1; j<= arr.size()-1; ++j)
            {
                int a = arr[i];
                for(int index = i+1; index<=j-1; ++index) a^=arr[index];
                
                for(int k = j; k<=arr.size()-1; ++k)
                {
                    
                    int b = arr[j];
                    for(int index = j+1; index<=k; ++index) b^=arr[index];

                    if(a == b) ++count;
                }
            }
        }

        return count;
    }

    int countTriplets_left_accumulated(vector<int>& arr) {

        if(arr.size() <2) return 0;

        //what was repeated during last solution ? 
        // --> XOR accumulation, we can use a vector to note 0->i, note as acc
        //--> for any range [i, j-1] XOR accumulaion will be : acc[j-1]^acc[i-1] 
        // --> O(n^3)
        int count = 0;
        vector<int> acc(arr.size()+1, 0);

        for(int i = 1; i<acc.size(); ++i)
        {
            acc[i] = acc[i-1]^arr[i-1];
            cout<<acc[i]<< ",";
        }



        for(int i = 0; i<=arr.size()-2; ++i)
        {
            for(int j = i+1; j<= arr.size()-1; ++j)
            {
                int a = acc[i]^acc[j];
                for(int k = j; k<=arr.size()-1; ++k)
                {
                    
                    int b = acc[j]^acc[k+1];

                    if(a == b) ++count;
                }
            }
        }
        return count;
    }


    int countTriplets_left_accumulated_smart_count(vector<int>& arr) {

        if(arr.size() <2) return 0;

        int count = 0;
        //can we do better? 
        //a == b --> a^b =0
        // if we can find any range [i,k] that XOR accumulation result is 0, we have k-i options for j
        //O(N^2)
        for(int i = 0; i<=arr.size()-2; ++i)
        {
            int acc = arr[i];
            for(int j = i+1; j<= arr.size()-1; ++j)
            {
                acc^=arr[j];
                if(acc ==0) count+= (j-i);
            }
        }
        return count;
    }

    int countTriplets_left_accumulated_historical_accumulation_pair(vector<int>& arr) {

        if(arr.size() <2) return 0;

        int count = 0;
        //can we do better? O(n) ?
        // what do we need to remove one more loop--> during the accumulation, if you found current result[0, j] has happened befor[0, i], that mean acc[i+1, j] = 0
        // --> we need a container to record the acc results and we need to access it in random time --> a map

        //unordered_map<int, vector<int>> accToIndex;
        unordered_map<int, array<int, 2>> accToIndexCountAndSum;
        int acc = 0;
        accToIndexCountAndSum[0] = {1, -1};  //particularly for the first 
        for(int i = 0; i<=arr.size()-1; ++i)
        {
            acc ^= arr[i];
            if(accToIndexCountAndSum.find(acc) != accToIndexCountAndSum.end())
            {
                // we found current index a, and previous indexes b and c have the same accumulation result: how many tuplets : a-(b+1) + a - (c+1)
                //--> in this case we don't need the vector, we just need a sum of b, c, then we use a*size - sum - size
                //--> change unordered_map<int, vector<int>> accToIndex; to unordered_map<int, arry<int,2>> accToIndexCountAndSum;
                const int howManySameAccs = accToIndexCountAndSum[acc][0];
                const int sumOfTheIndexes = accToIndexCountAndSum[acc][1];
                count += (howManySameAccs*i - howManySameAccs - sumOfTheIndexes);
            }

            //accToIndex[acc].push_back(i);
            ++accToIndexCountAndSum[acc][0];
            accToIndexCountAndSum[acc][1]+=i;
            
        }
        return count;
    }

    int countTriplets(vector<int>& arr) {
        return countTriplets_left_accumulated_historical_accumulation_pair(arr);
    }


}; 
