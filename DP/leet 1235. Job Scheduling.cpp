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
/*
1235. Maximum Profit in Job Scheduling

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

startTime = [1,  2, 3, 3], 
endTime =   [3,  4, 5, 6], 
   profit = [50,10,40,70]

for every task, I can choose take or not take
DP: 
    take: current profit + dfs(next task)
    don't take: dfs(current+1 task)
*/
class Solution {
private:
    using Start = int;
    using End = int;
    using Profit = int;
    using Task = tuple<Start, End, Profit>;
    int maxProfit(int from, const vector<Task>& tasks, vector<int>& memory){
        if(from == tasks.size()) return 0;

        auto& cache = memory[from];
        if(cache != -1) return cache;

        int profit = maxProfit(from+1, tasks, memory);// don't take current
        
        // take current
        {
            const auto& end = get<1>(tasks[from]);
            const auto& currentProfit = get<2>(tasks[from]);

            auto nextIndex = 
                lower_bound(tasks.begin(), tasks.end(), end, [](const Task& task, int end){
                    return  get<0>(task)< end; 
                }) 
                - tasks.begin();

            profit = max(profit, currentProfit+maxProfit(nextIndex, tasks, memory));
        }
        
        return cache = profit;

    }
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        vector<int> memory(startTime.size(), -1);
        vector<Task> tasks;tasks.reserve(startTime.size());

        for(int i=0; i<startTime.size(); ++i){
            tasks.emplace_back(startTime[i], endTime[i], profit[i]);
        }

        sort(tasks.begin(), tasks.end()); // sort by start time then end. then profit

        return maxProfit(0, tasks, memory);

        //O(nlogn)
    }
};


/*
 0   1   2   4
[1,  2,  3,  3]
[3,  4 , 5,  6]
[50,10, 40, 70]



*/
