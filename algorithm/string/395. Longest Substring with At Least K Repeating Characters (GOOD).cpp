
/*
Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.

 

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/
class Solution {
/*
fact:
    all letters should reach the frequence requirment

idea:
    1 brut force n^2  cehck all substrings
    2 sliding window -> when to slide left and when to slide right--> not really have the info when decide to shift left or right
    3 DP ? --> what will be the state ?  -> the histogram
        --> start from first ? we need at least n-1 "first letter" and at least n other letters ?--> not sure what letters, not sure what's the target ondition
        -->  

    4 recursive --> find bad points : when there is a bad point it we take all string and we cannot meet k  values for this letter, this point is a bad point, we should search intersections of bad points.


*/
public:
    int longestSubstring_brutforce(string s, int k) {// O(n^3)

        int maxLenth = 0;
        for(int first= 0; first<s.size(); ++first)
        {
            for(int last = first; last<s.size(); ++last)
            {
                unordered_map<char, int> histogram;
                for(int i = first; i<= last; ++i)
                {
                    ++histogram[s[i]];
                }

                bool valid = true;
                for(const auto & [c,v] : histogram)
                {
                    if(v<k) valid = false;
                }
                if(valid) maxLenth = std::max(maxLenth, last - first+1);
            }
        }
        return maxLenth;
    }



    int longestSubstring_range(string s, int k, int from, int to)
    {
        if(to - from + 1 < k) return 0;

        vector<int> histogram(26, 0);

        int maxLength = 0;
        for(int i = from; i<= to; ++i)
        {
             ++histogram[s[i] - 'a'];
        }

        bool valid = true;
        int lastBadPoint = from-1;
        for(int i = from; i<= to; ++i)
        {
            if(histogram[s[i] - 'a']<k)//Find "bad points"
            {
                maxLength = std::max(maxLength, longestSubstring_range(s, k , lastBadPoint+1, i-1));
                valid = false;
                lastBadPoint = i;
            }
        }

        if(valid) return to-from+1;

        
        maxLength = std::max(maxLength, longestSubstring_range(s, k , lastBadPoint+1, to));
        return maxLength;
    }

    int longestSubstring(string s, int k)
    { 
        return longestSubstring_range(s, k, 0, s.size() -1);
    }
};
