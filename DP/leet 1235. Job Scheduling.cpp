  /*
   We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.


[1,2,3,3]
[3,4,5,6]
[50,10,40,70]
[1,2,3,4,6]
[3,5,10,6,9]
[20,20,100,70,60]
[1,1,1]
[2,3,4]
[5,6,4]

    */
class Solution {
private:
    int jobSchedulingFrom(const vector<vector<int>>& tasks, int i,
                      vector<int>& dp) {
        if (i >= tasks.size()) return 0;
        if (dp[i] != -1) return dp[i];

        // skip task i
        int res = jobSchedulingFrom(tasks, i + 1, dp);

        // take task i → binary search for next non-overlapping task
        int nextIdx = lower_bound(tasks.begin() + i + 1, tasks.end(), tasks[i][1],
            [](const vector<int>& t, int endTime) { return t[0] < endTime; }
        ) - tasks.begin();

        res = max(res, tasks[i][2] + jobSchedulingFrom(tasks, nextIdx, dp));
        return dp[i] = res;
    }

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        // DP: 
        vector<int> dp(startTime.size(), -1);

        vector<vector<int>> sortedTasks; sortedTasks.reserve(startTime.size());
        for(int i=0; i<startTime.size(); ++i){
            sortedTasks.push_back({startTime[i], endTime[i], profit[i]});
        }

        sort(sortedTasks.begin(), sortedTasks.end());

        return jobSchedulingFrom(sortedTasks, 0, dp);
    }

};


/*
 0   1   2   4
[1,  2,  3,  3]
[3,  4 , 5,  6]
[50,10, 40, 70]



*/
