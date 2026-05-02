/*
1415. The k-th Lexicographical String of All Happy Strings of Length n
Medium
Topics
Companies
Hint
A happy string is a string that:

consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

 

Example 1:

Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
Example 2:

Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.
Example 3:

Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
 

Constraints:

1 <= n <= 10
1 <= k <= 100
*/


/*
Fact:
    1 only ['a', 'b', 'c'].
    2 s[i] != s[i + 1] , no adjacent duplication
    3 length n will make a list of happy strings in order: the length of this list is 3*2^(n-1) 

Idea:
    1 the results is a tree of 3 nodes in first level and 2 nodes in rest levels
        --> if it's a full binary tree, how to do it? 

                    null
                    a          b
                    a    b     a     b
                    a  b a  b  a  b  a  b 
                    0  1 2  3  4  5  6   7

                    0 aaa
                    1 aab
                    3 abb

                -> 0 and 1, for example 5 = 101, so it's b a b,
                but now we have 3 choice in first level, like [0 1 2] [0 1] [0 1], similar idea, just use 3 instead 2 in the first level





*/
class Solution {
public:
    string getHappyString(int n, int k) {
        --k;

        int totalNumber = 3;
        for(int i=n-1; i>0; --i){
            totalNumber*=2;
        }

        if(totalNumber<=k) return "";

        string res(n, 'a');
        for(int i=n-1; i>0; --i){
            res[i] = k%2;
            k/=2;
        }

        res[0] = 'a'+k%3;

        for(int i = 1; i<n; ++i){
            if(res[i-1]=='a'){
                res[i]=res[i]+'b';
            }else if(res[i-1]=='c'){
                res[i]=res[i]+'a';
            }else{
                if(res[i]==0){
                    res[i]='a';
                }
                else{
                    res[i]='c';
                }
            }
        }

        return res;
    }
};
