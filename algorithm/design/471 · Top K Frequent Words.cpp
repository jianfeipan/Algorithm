class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        /*
        1 we need to count -> hashMap count
        2 to get top k ->maxHeap
        */
        
        unordered_map<string, int> wordsCount;
        for(const auto & word:words) ++wordsCount[word];
        
        auto less = [](const pair<int, string> & left, const pair<int, string> & right){
            if(left.first == right.first) return left.second > right.second;
            else return left.first < right.first;
        };
        
        priority_queue<
            pair<int, string>,
            vector<pair<int, string>>, 
            decltype(less) > maxHeap(less);//!!pay attention!!
        for(const auto & [word, count] : wordsCount) maxHeap.push({count, word});
        
        vector<string> topK;
        while(k-- && !maxHeap.empty())
        {
            topK.push_back(maxHeap.top().second);maxHeap.pop();
        }
        
        return topK;
    }
};
