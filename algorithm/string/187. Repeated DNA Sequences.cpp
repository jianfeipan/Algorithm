class Solution {
/*
187. Repeated DNA Sequences
Medium
3.2K
512
Companies
The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.

For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.

Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

 

Example 1:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]
Example 2:

Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]
 

Constraints:

1 <= s.length <= 105
s[i] is either 'A', 'C', 'G', or 'T'.

*/


/*
idea：
 well int he begining I think there was one algo for searching prefix or something else, but I don't remember. then I think we can do a brut force, then I realize that this is a good solution. 

*/
private:
    vector<string> findRepeatedDnaSequences_brut_force(string s) {//use a map to count all substr with size 10 O(N)
        if(s.size()<=10) return {};

        vector<string> res;
        unordered_map<string, int> counts;
        for(int i=0; i<=s.size()-10; ++i){
            auto substr = s.substr(i, 10);
            ++counts[substr];
        }
        for(const auto& [str, count] : counts){
            
            if(count>1){
                res.insert(res.end(), 1, str);
            }
        }

        return res;
    }

public:
    vector<string> findRepeatedDnaSequences(string s) {
        return findRepeatedDnaSequences_brut_force(s);
    }
};
