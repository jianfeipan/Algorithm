/*
A company has limited resources, 
it can only finish at most k distinct projects before the IPO. 
Help the company to design the best way to maximize its total capital 
after finishing at most k distinct projects.

You are given n projects 
where the ith project has a pure profit profits[i] 
and a minimum capital of capital[i] is needed to start it. 

Initially, you have w capital. When you finish a project, 
you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of at most k distinct projects from given projects 
to maximize your final capital, and return the final maximized capital.

The answer is guaranteed to fit in a 32-bit signed integer.

Example 1:

Input: k = 3, w = 0, profits = [1,4,2,3], capital = [0,3,1,1]
         0 1 2 3
        [1,4,2,3]
        [0,3,1,1]
       capital       
initial 0
take0: +1
take3: +3 = 4
take1: +4 = 8



Output: 8
Explanation : The order of indices to pick are [0,3,1] and final capital is (1 + 3 + 4) = 8.

Example 2:

Input: k = 4, w = 2, profit = [2,3,1,5,3], capital = [4,4,2,3,3]

Output: 14

Greedy: 
    with current capital, we have choices, and we take the most profitable tasks
    
*/
/*
A company has limited resources, 
it can only finish at most k distinct projects before the IPO. 
Help the company to design the best way to maximize its total capital 
after finishing at most k distinct projects.

You are given n projects 
where the ith project has a pure profit profits[i] 
and a minimum capital of capital[i] is needed to start it. 

Initially, you have w capital. When you finish a project, 
you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of at most k distinct projects from given projects 
to maximize your final capital, and return the final maximized capital.

The answer is guaranteed to fit in a 32-bit signed integer.

Example 1:

Input: k = 3, w = 0, profits = [1,4,2,3], capital = [0,3,1,1]
         0 1 2 3
        [1,4,2,3]
        [0,3,1,1]
       capital       
initial 0
take0: +1
take3: +3 = 4
take1: +4 = 8



Output: 8
Explanation : The order of indices to pick are [0,3,1] and final capital is (1 + 3 + 4) = 8.

Example 2:

Input: k = 4, w = 2, profit = [2,3,1,5,3], capital = [4,4,2,3,3]

Output: 14

Greedy: 
    with current capital, we have choices, and we take the most profitable tasks
    
*/

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        const auto& n = profits.size();
        using Profit = int;
        using Task = int;
        
        // very good exmaple of managing index
        vector<Task> taskIndexByCapital(n);
        for(int i =0; i<n;++i) taskIndexByCapital[i] = i;

        sort(taskIndexByCapital.begin(), taskIndexByCapital.end(), [&](int left, int right){
            return capital[left] < capital[right];
        });//--> sort by capture of the capital!!!

        priority_queue<Profit> maxHeap;
        auto indexIt = taskIndexByCapital.begin();
        for(int i=0; i<k; ++i){
            // push availiable tasks
            while(indexIt != taskIndexByCapital.end() 
            && capital[*indexIt] <= w){
                maxHeap.push(profits[*indexIt]);
                ++indexIt;
            }
            
            if(maxHeap.empty()) break;

            auto maxProfit = maxHeap.top();maxHeap.pop();
            w+=maxProfit;
        }

        return w;
    }
};
