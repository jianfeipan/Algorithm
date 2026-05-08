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

#include <unordered_map>
#include <queue>

using namespace std;
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // always prioritize the taks with hight frequence
        array<int, 26> freq{};
        for(auto task : tasks) ++freq[task - 'A'];

        // most frequent tasks-> maxHeap
        using Freq = int;
        using Task = pair<Freq, char>;
        priority_queue<Task> to_process; 

        // earlise can be processed : a normal queue is ok! we push it with time order, if cool down time is not the same, t+n[i] , this we need a minHeap
        using EndCooling = int;
        using CoolingTask = pair<EndCooling, Task>;
        queue<CoolingTask> cool_down;

        for(int i=0; i<26; ++i) if(freq[i]>0) to_process.push({freq[i], 'A'+i});

        int t = 0;
        while(!to_process.empty() || !cool_down.empty()){
            //check cool_down queue, and bring tasks back to to_process queue if they are cooled down
            while( !cool_down.empty() && cool_down.front().first < t ){
                to_process.push(cool_down.front().second); cool_down.pop();
            }

            //take task from to_process, process it, put it to cool down queue
            if(!to_process.empty()){
                auto task = to_process.top(); to_process.pop();
                --task.first;
                if(task.first>0) cool_down.push( {t+n, task} ); // if tasks still have freq
                ++t;
            }else{
                
                t = max(t+1, cool_down.front().first);
            }
        }
        return t;
    }
};

