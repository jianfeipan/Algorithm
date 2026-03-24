/*LeetCode 340: Longest Substring with At Most K Distinct Characters

You are given a string s and an integer k,
 and you need to find the length of the longest substring that contains
  no more than k distinct characters.
  
  idea:
    sliding window, with a set to count distinct letters
  
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int l = 0;
        int r = 0;
        int longestDistinct = 1;
        std::unordered_map<char, int> letters;
        ++letters[s[0]];
        while(r<s.size()){
            if(letters.size() <= k){
                ++r;
                if(r<s.size()){
                    ++letters[s[r]];
                    longestDistinct = max(longestDistinct, r - l +1);
                }else{
                    break;
                }
            }else{
                while(letters.size() > k){
                    --letters[s[l]];
                    if(letters[s[l]]==0){
                        letters.erase(s[l]);
                    }
                    ++l;
                }
            }
        }
        return longestDistinct;
    }
};

// --- Testing Infrastructure ---
void runTest(string s, int k, int expected) {
    Solution sol;
    int result = sol.lengthOfLongestSubstringKDistinct(s, k);
    cout << "Input: s = \"" << s << "\", k = " << k << endl;
    cout << "Result: " << result << " | Expected: " << expected;
    if (result == expected) {
        cout << " [PASS]" << endl;
    } else {
        cout << " [FAIL]" << endl;
    }
    cout << "---------------------------------------" << endl;
}

int main() {
    runTest("eceba", 2, 3); // Substring "ece"
    runTest("aa", 1, 2);    // Substring "aa"
    runTest("a", 0, 0);     // k is 0
    runTest("world", 4, 4); // Substring "worl"
    
    return 0;
}
