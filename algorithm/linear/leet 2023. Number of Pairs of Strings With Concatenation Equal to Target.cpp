class Solution {
public:
    int numOfPairs(vector<string>& ss, string target) 
    {
        int count = 0;
        unordered_map<string, int> words;
        
        for(const auto & s : ss)
        {
            //find in the map the string I need
            vector<string> needed = findNeededStr(s, target);
            for(const auto neededStr : needed)
            {
                if(words.count(neededStr))  count += words[neededStr];              
            }
            words[s]++;
        }
        
        return count;
    }
    
private:
    vector<string> findNeededStr(const string & part, const string & target)
    {
        vector<string> needed;
        if(part.size() < target.size())
        {
            size_t pos = target.find(part);
            while(pos!=string::npos)
            {
                if(pos == 0) needed.push_back(target.substr(part.size()));
                else if(pos + part.size() == target.size()) needed.push_back(target.substr(0, pos));
                
                pos = target.find(part,pos+1);
            }
        }
        return needed;
        
    }
};
