/*
You are given an array of integers temperatures where temperatures[i] represents the daily temperatures on the ith day.

Return an array result where result[i] is the number of days after the ith day before a warmer temperature appears on a future day. If there is no day in the future where a warmer temperature will appear for the ith day, set result[i] to 0 instead.

Example 1:

Input: temperatures = [30,38,30,36,35,40,28]

Output: [1,4,1,2,1,0,0]
Example 2:

Input: temperatures = [22,21,20]

Output: [0,0,0]
Constraints:

1 <= temperatures.length <= 1000.
1 <= temperatures[i] <= 100
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        const auto& n = temperatures.size();
        vector<int> res(n, 0);
        // number of days to a warmer day

        //BF O(n^2)
        
        // Monoton stack -> current day will pop all left lower days

        stack<int> pastIndex;

        for(int i = 0; i< temperatures.size(); ++i){
            auto temp = temperatures[i];
            while(!pastIndex.empty() && temperatures[pastIndex.top()] < temp) {
                auto colderDay = pastIndex.top();
                res[colderDay] = i - colderDay;
                pastIndex.pop();
            }
            pastIndex.push(i);
        }
        return res;
    }
};
