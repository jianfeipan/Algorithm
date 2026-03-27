class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // there is an order relation between intervals and queries
        using LengthEnd = vector<int>;
        priority_queue<LengthEnd, vector<LengthEnd>, greater<LengthEnd>> minLens;

        sort(intervals.begin(), intervals.end());
        auto sortedQueries = queries; 
        // !!!! when your reslt depends on input order and you are doing sort, make a copy
        sort(sortedQueries.begin(), sortedQueries.end()); 
        //when you sort it , result cannot relie on index need a map
        unordered_map<int, int> minlenForValue;
        
        int left = 0;
        for(int q = 0; q < sortedQueries.size(); ++q){
            const auto& target = sortedQueries[q];
            // for each target we push the intervals start on left of target [[[[[ *  ...
            // this is monoton!!! we don't need to push them again for next target, because it's bigger
            while(left < intervals.size() && intervals[left][0] <= target){
                const auto len = intervals[left][1] - intervals[left][0] + 1;
                minLens.push({len, intervals[left][1]});

                ++left;
            }

            while(!minLens.empty() && minLens.top()[1] < target){
                minLens.pop(); 
                // those intervals close before taget, for sure wont include taret and next target
            }
            minlenForValue[target] = minLens.empty() ? -1 : minLens.top()[0];
        }

        vector<int> res(queries.size());
        for(int i=0; i<queries.size(); ++i){
            res[i] = minlenForValue[queries[i]];
        }

        return res;

    }


    vector<int> minInterval_BF(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> res;
        for(auto& query : queries){ //O(I*Q)
            int minLen = INT_MAX;
            for(auto& interval : intervals){
                if(interval[0]<= query && query <= interval[1]){
                    minLen = min(minLen, interval[1] - interval[0]+1);
                }
            }
            res.push_back(minLen == INT_MAX ? -1 : minLen);
        }
        return res;
    }
};
