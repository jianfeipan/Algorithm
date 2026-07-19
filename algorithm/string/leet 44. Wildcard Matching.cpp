/*
Match a string with wildcard pattern recursively
for exmale: abcd matches a*cd, or a.cd or a*d
always a letter before * means zero , one or more of that letter, and . means any single character
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Recursively match string s (starting at si) against pattern p (starting at pi).
// Rules:
//   '.' matches any single character
//   '*' preceded by a letter means zero or more of that letter
bool match(const string& s, const string& p, 
                 int fromS, int fromP){
    if(fromP == p.size()) return fromS == s.size();

    bool starPattern = ( fromP<p.size()-1 && p[fromP+1] == '*');
    if(fromS == s.size()){
        if(starPattern) return isMatch(s, p, fromS, fromP+2);
    }


    // exact match
    if(s[fromS] == p[fromP] || p[fromP] == '.'){
        if(starPattern){
            // abc a*, .*,
            return isMatch(s, p, fromS+1, fromP+2)// match and consum the .*
                || isMatch(s, p, fromS+1, fromP) // match reuse .*
                || isMatch(s, p, fromS, fromP+2); // .* matches nothing
        }else{
            // abc ac , .c
            return isMatch(s, p, fromS+1, fromP+1);
        }
    }else{
        if(starPattern){// abc, b*
            return isMatch(s, p, fromS, fromP+2); // b* missmatch
        }else{// abc, d
            return false;
        }
    }
} 

bool match(const string& s, const string& pattern) {
    return match(s, 0, pattern, 0);
}

int main() {
    // Basic tests from the comment
    assert(match("abcd", "a*cd") == false);   // 'a*' = zero or more 'a', then "cd" — "abcd" has 'b' which doesn't match
    assert(match("aacd", "a*cd") == true);     // 'a*' = two 'a's, then "cd"
    assert(match("cd", "a*cd") == true);       // 'a*' = zero 'a's, then "cd"
    assert(match("acd", "a*cd") == true);      // 'a*' = one 'a', then "cd"

    assert(match("abcd", "a.cd") == true);     // '.' matches 'b'
    assert(match("axcd", "a.cd") == true);     // '.' matches 'x'
    assert(match("acd", "a.cd") == false);     // '.' must match exactly one char

    assert(match("abcd", "a.*d") == true);     // '.*' matches "bcd"... actually "bc", then 'd'
    assert(match("ad", "a.*d") == true);       // '.*' matches zero chars, then 'd'
    assert(match("abcd", ".*") == true);       // '.*' matches everything

    assert(match("abc", "abc") == true);       // exact match
    assert(match("abc", "ab") == false);       // incomplete pattern
    assert(match("ab", "abc") == false);       // string shorter than pattern
    assert(match("", "") == true);             // both empty
    assert(match("", "a*") == true);           // 'a*' matches zero 'a's
    assert(match("aaa", "a*") == true);        // 'a*' matches three 'a's
    assert(match("b", "a*") == false);         // 'a*' = zero or more 'a', doesn't match 'b'

    cout << "All tests passed!" << endl;
    return 0;
}
