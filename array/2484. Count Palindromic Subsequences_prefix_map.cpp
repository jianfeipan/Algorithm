#include <array>
class Solution {
public:
    int countPalindromes(string s) {
        if(s.size()<5) return 0;
        int mod = 1e9 + 7;
        const auto n=s.size();
        vector<array<array<int, 10>, 10>> before(n);
        {// before i, counts of A_B
            array<int, 10> count;
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
            array<int, 10> count;
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
        for (int i = 2; i <= n - 2; i++){
            for (int a = 0; a < 10; a++)
                for (int b = 0; b < 10; b++)
                    ans = (ans + 1LL * before[i - 1][a][b] * after[i + 1][a][b]) % mod;
        }
        return ans;
            

    }
};
