class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        unordered_map<char, int> diagram;
        for(char c : chars) ++diagram[c];
        
        int totalCount = 0;
        for(const auto & word : words)
        {
            unordered_map<char, int> count = diagram;
            for(char c : word) --count[c];

            totalCount+=word.size();
            for(auto [c, nb] : count) 
            {
                if(nb<0) 
                {
                    totalCount-=word.size();
                    break;        
                }
            }
        }
        
        return totalCount;
    }
};
