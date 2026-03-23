#include <iostream>
#include <vector>
#include <cassert>
/*
You are given an integer length 
(the size of an array initialized to all zeros) and a list of updates.
Each update is a triplet: [start_index, end_index, increment].

Example 
Input: length = 5, updates = [[1, 3, 2]]

Initialize: [0, 0, 0, 0, 0]

Apply Update: [0, 2, 2, 2, 0]

*/


/*
length = N; modifications K
Brute Force: O(K*N)

  

*/
using namespace std;

class Solution {
public:
    /**
     * @param length: The length of the array
     * @param updates: A list of triplets [startIndex, endIndex, inc]
     * @return: The modified array
     */
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> res(length, 0);
        /*
                       0 1 2 3 4
                      [0 0 0 0 0]
         {1, 3, 2},      2 2 2
         {2, 4, 3},        3 3 3
         {0, 2, -2}   -2-2-2
                     [-2 0 3 5 3]

         all ranges are [from, to], we can transform them to leftSum[l-1] - leftSum[r]      
          {1, 3, 2} -> {0, 3, 2} + {0, 0, -2}
          {2, 4, 3} -> {0, 4, 3} + {0, 1, -3}
          {0, 2,-2} -> {0, 2,-2}

          so we have, they are piece-wise shifters: 0 shift -1, then piece-wise, then 1 shift -3...
          we place these shifters on the [0 0 0 00 0 0 0 0 0 ]
          and we do accumulate from left, it ill be the final result
                     
          
        */
        
        for (const auto& update : updates) {
            const auto& left = update[0];
            const auto& right = update[1];
            const auto& increment= update[2];
            
            /* 
              transform range to "left side jumps" 
                right index jump val
                left-1 index jump -val
            */
            res[right] += val;
          
            if (left>0) {
                res[left-1] -= val;
            }
        }
        // we do accumulate from right, piece-wise the jumps
        for(int i=res.size()-2; i>=0; --i) res[i]+=res[i+1];
        
        return res;
    }
};

// Helper function to print the array for debugging
void printArray(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Test Case 1: Standard example
    int len1 = 5;
    vector<vector<int>> updates1 = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
    vector<int> expected1 = {-2, 0, 3, 5, 3};
    vector<int> result1 = sol.getModifiedArray(len1, updates1);
    
    cout << "Test Case 1: ";
    printArray(result1);
    assert(result1 == expected1);

    // Test Case 2: Overlapping ranges
    int len2 = 10;
    vector<vector<int>> updates2 = {{2, 4, 6}, {5, 6, 8}, {1, 9, -4}};
    vector<int> expected2 = {0, -4, 2, 2, 2, 4, 4, -4, -4, -4};
    vector<int> result2 = sol.getModifiedArray(len2, updates2);
    
    cout << "Test Case 2: ";
    printArray(result2);
    assert(result2 == expected2);

    // Test Case 3: Single element update
    int len3 = 3;
    vector<vector<int>> updates3 = {{0, 0, 5}, {2, 2, -1}};
    vector<int> expected3 = {5, 0, -1};
    vector<int> result3 = sol.getModifiedArray(len3, updates3);

    cout << "Test Case 3: ";
    printArray(result3);
    assert(result3 == expected3);

    cout << "\nAll test cases passed!" << endl;

    return 0;
}
