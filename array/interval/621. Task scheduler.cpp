/*
You are given an array of CPU tasks tasks, where tasks[i] is an uppercase english character from A to Z. You are also given an integer n.

Each CPU cycle allows the completion of a single task, and tasks may be completed in any order.

The only constraint is that identical tasks must be separated by at least n CPU cycles, to cooldown the CPU.

Return the minimum number of CPU cycles required to complete all tasks.

Example 1:

Input: tasks = ["X","X","Y","Y"], n = 2

Output: 5
Explanation: A possible sequence is: X -> Y -> idle -> X -> Y.

Example 2:

Input: tasks = ["A","A","A","B","C"], n = 3

Output: 9
Explanation: A possible sequence is: A -> B -> C -> Idle -> A -> Idle -> Idle -> Idle -> A.

Constraints:

1 <= tasks.length <= 1000
0 <= n <= 100

*/

class Solution {
public:
/*
facts:
    1.Each CPU cycle allows the completion of a single task,
    2.tasks may be completed in any order
    3.identical tasks must be separated by at least n CPU cycles

ideas:
    process from the most frequent one -> maxHeap
    once processed, this is moved from the maxHeap and put it to the collDown queue
    -> the coolDown queue need to know when it's good again to be processed 
    by using a timer!
    when this time reaches it moved from cool down queue to the maxHeap again.

    complexity: go over all  N tasks, maybe with n coll down time O(N*n)
*/

    int leastInterval(vector<char>& tasks, int n) {
        vector<int> frequency(26, 0);
        for(const auto& task:tasks) ++frequency[task-'A'];

        //maxHeap: to be processed
        priority_queue<int> toBeProcessed;
        for(auto f : frequency){
            if(f>0) toBeProcessed.push(f);
        }

        queue<pair<int, int>> cooldownTime_frequence;

        int t = 0;
        while(!toBeProcessed.empty() || !cooldownTime_frequence.empty()){
            ++t;
            if(!toBeProcessed.empty()){
                const auto topFrequency = toBeProcessed.top();toBeProcessed.pop();
                if(topFrequency>1)
                    cooldownTime_frequence.push({ t+n, topFrequency-1});
            }
            else{//nothing to process, let's jump to the cooldownque
                t = cooldownTime_frequence.front().first;
            }

           

            if(!cooldownTime_frequence.empty()){
                const auto earliestCoolTask = cooldownTime_frequence.front();
                if(earliestCoolTask.first <= t){
                    toBeProcessed.push(earliestCoolTask.second);
                    cooldownTime_frequence.pop();
                }
            }
        }

        return t;
    }
};
