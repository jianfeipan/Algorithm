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
        unordered_map<char, int> freq;
        for(auto t : tasks) ++freq[t];

        // take the most frequent 
        priority_queue<int> to_process;
        for(const auto& [_, f]:freq) to_process.push(f);

        // cool down task: time_freq
        using TimeFreq = pair<int, int>;
        queue<TimeFreq> cool_down;

        int t = 0;
        while(!to_process.empty() || !cool_down.empty()){
            ++t;
            if(!to_process.empty()){
                
                auto most_freq = to_process.top(); to_process.pop();
                // the rest of the same task should be process at t+n
                if(most_freq>1) cool_down.push({t+n, most_freq-1});
            } else {
                auto [earlist, _] = cool_down.front();
                t = earlist;
            }

            if(!cool_down.empty()){
                auto [earlist, freq] = cool_down.front();
                if(t>=earlist){
                    cool_down.pop();
                    to_process.push(freq);
                } 
            }
        }
        
        return t;
    }
};
