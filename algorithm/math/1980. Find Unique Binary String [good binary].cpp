/*
1980. Find Unique Binary String
Medium
1.9K
67
Companies
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

 

Example 1:

Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.
Example 2:

Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.
Example 3:

Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
 

Constraints:

n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.
*/
class Solution {
/*
    fact:
        number of digit is fixed, then we have the range 00,01, 10, 11


    idea:
        find the number of digit, then mark the presernted ones, and loop the space, take the first one not marked 
*/

private:
    int toInt(const string & num){
        
        int res = 0;
        for(const auto & digit : num){
            res*=2;
            res+=(digit-'0');
        }

        // cout<<num<<" toInt "<<res<<endl;
        return res;
    }

    string toStr(int num, int count){
        cout<<num;
        string res(count, '0');
        for (auto it = res.rbegin(); it != res.rend(); ++it){
       
            (*it)+=num%2;
            num/=2;
        }
        // cout<<" tostr "<<res<<endl;

        return res;
    }
public:
    string findDifferentBinaryString_brut_force(vector<string>& nums) {
        const int count = nums[0].size();
        const int size = (1<<count);

        vector<bool> avaliable_num(size, true);

        for(const auto & num : nums){
            avaliable_num[toInt(num)] = false;
        }

        for(int i=0; i<size;++i){
            if(avaliable_num[i]) return toStr(i, count);
        }

        return "";

        
    }

    



    /*
    improivement: easy solution: make a different digit by digit!! binary 's charactor: every digit is different from one of the inputs, you will be unique !!!!

     string findDifferentBinaryString(vector<string>& nums) {
        string ans = "";
        int i = 0;
        for(string &s: nums){
            ans += s[i++] == '0'?'1':'0';
        }
        return ans;
    }
    
    
    
    */

    string findDifferentBinaryString(vector<string>& nums) {
        string ans = "";
        int i = 0;
        for(string &s: nums){
            ans += s[i++] == '0'?'1':'0';
        }
        return ans;
    }
};
