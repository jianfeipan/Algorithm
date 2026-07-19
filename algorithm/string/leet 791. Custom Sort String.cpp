class Solution {
  
  /*
  You are given two strings order and s. All the words of order are unique and were sorted in some custom order previously.

Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.

Return any permutation of s that satisfies this property.

 

Example 1:

Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
Example 2:

Input: order = "cbafg", s = "abcd"
Output: "cbad"
  */
public:
    string customSortString(string order, string s) {
        //Idea: find "s" chars which are in "order" chars, then put the rest 
        string sorted;
        
        unordered_map<char, size_t> dict;
        
        for(char c : order)
            dict[c] = 0;
        string rest; 
        for(char c:s)
            if(dict.count(c)) ++dict[c];
            else rest+=c;
        
        
        for(char c : order)
        {
            if(dict[c] > 0)
                sorted+=string(dict[c], c);
        }
        
        return sorted+rest;
    }
};
