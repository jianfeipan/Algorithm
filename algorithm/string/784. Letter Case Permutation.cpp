/*
784. Letter Case Permutation
Medium
Topics
Companies
Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the output in any order.

 

Example 1:

Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]
Example 2:

Input: s = "3z4"
Output: ["3z4","3Z4"]
 

Constraints:

1 <= s.length <= 12
s consists of lowercase English letters, uppercase English letters, and digits.


*/


/*

facts:
    1 ignore numbers,
    2 up/low two case for letter

idea: 
    1 loop original one and generate more in a vector

*/


class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> res{s};


        for(int i=0; i<=s.size();++i){
            if(s[i]>='a' &&  s[i]<='z'){
                vector<string> more;
                for(string scopy: res){
                    scopy[i]+=('A'-'a');
                    more.push_back(std::move(scopy));
                }
                res.insert(res.end(), more.begin(), more.end());
            }
            else if(s[i]>='A' &&  s[i]<='Z'){
                vector<string> more;
                for(string scopy: res){
                    scopy[i]+=('a'-'A');
                    more.push_back(std::move(scopy));
                }
                res.insert(res.end(), more.begin(), more.end());
            }
        }

        return res;
    }
};
