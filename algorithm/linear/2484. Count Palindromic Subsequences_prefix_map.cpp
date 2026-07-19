#include <array>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int countPalindromes(string s) {
        const auto n=s.size();
        if (n < 5) return 0;

        int mod = 1e9 + 7;
        vector<array<array<int, 10>, 10> > before(n);
        {// before i, counts of A_B
            array<int, 10> count{};
            ++count[s[0] - '0'];
            for(int i=1; i<n; ++i){
                int current = s[i] - '0';
                before[i] = before[i-1];
                for(int a=0; a<10;++a)
                    before[i][a][current] += count[a];// += how Many A so far
                ++count[current];
            }
        }
        vector<array<array<int, 10>, 10>> after(n);

        {// after i, counts of A_B: from right to left
            array<int, 10> count{};
            ++count[s[n-1] - '0'];
            for(int i=n-2; i>=0; --i){
                int current = s[i] - '0';
                after[i] = after[i+1];
                for(int a=0; a<10;++a)
                    after[i][a][current] += count[a];// += how Many A so far
                ++count[current];
            }
        }
        int ans=0;
        for (int i = 2; i <= (int)n - 3; i++){
            for (int a = 0; a < 10; a++)
                for (int b = 0; b < 10; b++)
                    ans = (ans + 1LL * before[i - 1][a][b] * after[i + 1][a][b]) % mod;
        }
        return ans;


    }
};

#include <iostream>
#include <cassert>

int main() {
    Solution sol;

    // Test 1: Example from LeetCode – "103301"
    // Palindromic subsequences of length 5: e.g., "10301", "## 10001", "13031", etc.
    assert(sol.countPalindromes("103301") == 2);

    // Test 2: All same digits – "00000"
    // Only one distinct palindrome pattern but C(5,5)=1
    assert(sol.countPalindromes("00000") == 1);

    // Test 3: Minimum length that can't form length-5 subsequence
    assert(sol.countPalindromes("0000") == 0);

    // Test 4: Exactly length 5, all same
    assert(sol.countPalindromes("11111") == 1);

    // Test 5: Exactly length 5, a palindrome
    assert(sol.countPalindromes("12321") == 1);

    // Test 6: Exactly length 5, not a palindromic subsequence match
    assert(sol.countPalindromes("12345") == 0);

    // Test 7: Longer string with repeated digits – "0000000" (7 zeros)
    // C(7,5) = 21 palindromic subsequences (all "00000")
    assert(sol.countPalindromes("0000000") == 21);

    // Test 8: Two distinct digits – "9999900000"
    {
        int result = sol.countPalindromes("9999900000");
        std::cout << "Test 8 (9999900000): " << result << std::endl;
        assert(result > 0);
    }

    // Test 9: Single repeated pattern – "1234321"
    {
        int result = sol.countPalindromes("1234321");
        std::cout << "Test 9 (1234321): " << result << std::endl;
        assert(result > 0);
    }

    // Test 10: Large input – all '1's, length 1000
    // C(1000,5) mod 1e9+7
    {
        std::string s(1000, '1');
        int result = sol.countPalindromes(s);
        std::cout << "Test 10 (1000 ones): " << result << std::endl;
        assert(result > 0);
    }

    // Test 11: Empty string
    assert(sol.countPalindromes("") == 0);

    // Test 12: Length 5 with digits forming no palindrome subsequence
    assert(sol.countPalindromes("13579") == 0);

    // Test 13: "abba"-like numeric pattern "12344321"
    {
        int result = sol.countPalindromes("12344321");
        std::cout << "Test 13 (12344321): " << result << std::endl;
        assert(result > 0);
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
