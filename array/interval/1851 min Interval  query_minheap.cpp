/*
intervals = [[1,3],[2,3],[3,7],[6,6]], 
queries = [2,3,1,7,6,8]

2: [1,3],[2,3]
3: [1,3],[2,3],[3,7]
1: [1,3]
7: [3,7]
6: [3,7][6,6]
8:..
BF: O(I*Q)
for each query Q, check all intervals I: Q*I

can we only scan I once? 
sorting -> Q and I by start

look at the timeline: 

[ [ q1[ [ [q2 [ [ [q3 [ [ 

q1 can only be covered by I  "start before q1", -> candidates -> push
q1 can only be covered by I  "end after q1", -> filter -> pop
then we need the order of length (end - start+1) -> target -> minHeap (logI)

*/


class Solution_sort_minHeap {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        using Query = int;
        using Index = int;
        map<Query, vector<Index>> sortedQs; // duplicated queries in different index
        for(int i=0; i<queries.size(); ++i) sortedQs[queries[i]].push_back(i);

        sort(intervals.begin(), intervals.end()); // O(IlogI)

        using Len = int;
        using End = int;
        using IbyLen = pair<Len, End>;
        priority_queue<IbyLen, vector<IbyLen>, greater<IbyLen>> minHeap; //O(QlogQ)

        vector<int> minLen(queries.size(), 0); 
        int i = 0; // interval index
        for(const auto& [q, qis]: sortedQs){
            // push candidates start before q
            while(i<intervals.size() && intervals[i][0] <= q){
                const auto& start = intervals[i][0];
                const auto& end = intervals[i][1];
                minHeap.push({ end - start +1, end});
                ++i;
            }

            // pop filtered end before q
            while(!minHeap.empty() && minHeap.top().second < q) minHeap.pop();

            // the top is the min len
            for(auto qi : qis)
                minLen[qi] = minHeap.empty() ? -1 : minHeap.top().first;
        }

        return minLen;
    }
};
