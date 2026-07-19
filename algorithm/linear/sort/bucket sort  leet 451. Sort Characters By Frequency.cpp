/*

Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

 

Example 1:

Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
*/



class Solution {
public:
    string frequencySort(string s) 
    {
        return frequencySort_countingMap_bucketSort(s);
    }
    
    string frequencySort_countingMap_bucketSort(string s) //O(N)
    {
        unordered_map<char, size_t> diagram;
        
        for(char c :s) ++diagram[c];
        
        vector<string> bucket(s.size()+1, ""); //bucket is like a bit map or a hash map
        
        for(const auto & [c, count] : diagram) bucket[count]+=c;
        
        string output;
        for(int i = bucket.size()-1; i>=0; --i)
        {
            for(char c : bucket[i])
            output+=string(i, c);
        }
        
        return output;

    }

    
    string frequencySort_countingMap_quick_sort(string s) //O(NlogN)
    {
        unordered_map<char, size_t> diagram;
        
        for(char c :s) ++diagram[c];
        
        vector<pair<size_t, char>> order; order.reserve(diagram.size());
        
        for(const auto & [c, count] : diagram) order.emplace_back(count, c);
        sort(order.begin(), order.end(), greater());
        
        string output;
        for(const auto & c : order) output+=string(c.first, c.second);
        
        return output;
    }
};
