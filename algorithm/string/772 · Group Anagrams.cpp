class Solution {
public:
    /**
     * @param strs: the given array of strings
     * @return: The anagrams which have been divided into groups
     */
    vector<vector<string>> groupAnagrams(vector<string> &strs)
     {
        unordered_map<string, multiset<string>> group;//!!!!!multiset!!!alow duplications!!!
        for(const auto & str : strs)
        {
            string key(str);
            sort(key.begin(), key.end());
            //string key = strSort(str);
            group[key].insert(str);
        }

        vector<vector<string>> result;result.reserve(group.size());

        for(const auto & [key, value] : group)
        {
            vector<string> words(value.begin(), value.end());
            result.push_back(words);
        }

        return result;
    }

    vector<vector<string>> groupAnagrams_own_sort(vector<string>& strs) {
        unordered_map<string, multiset<string>> mp;
        for (string s : strs) {
            string t = strSort(s);
            mp[t].insert(s);
        }
        vector<vector<string>> anagrams;
        for (auto m : mp) { 
            vector<string> anagram(m.second.begin(), m.second.end());
            anagrams.push_back(anagram);
        }
        return anagrams;
    }
private:
    string strSort(const string & s) {//avery smart sort of only lowcase letters
        int count[26] = {0}, n = s.length();
        for (int i = 0; i < n; i++)
            count[s[i] - 'a']++;
        int p = 0;
        string t(n, 'a');
        for (int j = 0; j < 26; j++)
            for (int i = 0; i < count[j]; i++)
                t[p++] += j;
        return t;
    } 


};
