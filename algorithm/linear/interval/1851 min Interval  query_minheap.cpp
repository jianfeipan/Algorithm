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
/*
                     l       r
Input: intervals = [[1,3],[2,3],[3,7],[6,6]], 
          queries = [2,3,1,7,6,8]
*/

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> min_interval(queries.size(), -1);
        
        vector<int> queries_index(queries.size());
        {// sort qureies
            for(int i=0; i<queries_index.size(); ++i) queries_index[i]=i;

            auto less = [&queries](int left, int right){ return queries[left] < queries[right]; };
            sort(queries_index.begin(), queries_index.end(), less);
        }

        sort(intervals.begin(), intervals.end());

        auto greater = [](const auto& left, const auto& right){ return (left[1] - left[0]) > (right[1] - right[0]); };
        priority_queue<vector<int>, vector<vector<int>>, decltype(greater)> minHeap(greater); 

        int cur = 0;
        for(auto index : queries_index){
            const auto& qurey = queries[index];
            // push intervals, start before qurey
            for(;cur<intervals.size() && intervals[cur][0] <= qurey; ++cur) minHeap.push(intervals[cur]);
           
            // pop intervals end before qurey:
            while(!minHeap.empty() && minHeap.top()[1] < qurey) minHeap.pop();
            
            if(!minHeap.empty()) min_interval[index] = minHeap.top()[1] - minHeap.top()[0] + 1;
        }
        return min_interval;
    }
};

