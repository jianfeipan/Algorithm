class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> grouped;
        for(const auto & str : strs)
        {
            string key(str);sort(key.begin(), key.end());
            grouped[key].push_back(str);
        }
        
        vector<vector<string>> result;result.reserve(grouped.size());
        for(const auto &[key, strs] :  grouped)
        {
            result.emplace_back(vector<string>{strs.begin(), strs.end()});
        }
        return result;
    }
};
