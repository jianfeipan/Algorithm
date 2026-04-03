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
bool match(const string& s, int si, const string& p, int pi) {
    // If pattern is exhausted, string must also be exhausted
    if (pi == (int)p.size()) {
        return si == (int)s.size();
    }

    // Check if next pattern char is '*' (look-ahead)
    bool starFollow = (pi + 1 < (int)p.size() && p[pi + 1] == '*');

    if (starFollow) {
        char ch = p[pi]; // the character before '*'

        // Try matching zero occurrences of ch — skip "c*" in pattern
        if (match(s, si, p, pi + 2)) {
            return true;
        }

        // Try matching one or more occurrences of ch
        int i = si;
        while (i < (int)s.size() && (ch == '.' || s[i] == ch)) {
            if (match(s, i + 1, p, pi + 2)) {
                return true;
            }
            i++;
        }
        return false;
    }

    // No star follows — current pattern char must match current string char
    if (si == (int)s.size()) {
        return false;
    }

    if (p[pi] == '.' || p[pi] == s[si]) {
        return match(s, si + 1, p, pi + 1);
    }

    return false;
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
