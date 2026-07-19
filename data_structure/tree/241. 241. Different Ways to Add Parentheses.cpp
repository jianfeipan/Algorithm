/*

241. Different Ways to Add Parentheses
Given a string expression of numbers and operators, 
return all possible results from computing all the different possible ways 
to group numbers and operators. You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
All the integer values in the input expression are in the range [0, 99].
1 <= expression.length <= 20

 do not have a leading '-' or '+' denoting the sign.
'+', '-', and '*'.
 

Example 1:

Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10
*/

/*
idea:
    compute(2*3-4*5) =
     - 2* compute(..., ...)
     - 2*3- compute(..., ...)
*/
class Solution {
private:
    int eval(int l, int r, char op){
        if(op == '+') return l + r;
        if(op == '-') return l - r;
        if(op == '*') return l * r;
        return 0;// throw exception: unsupported operation 
    }

    vector<int> diffWaysToCompute(int from, int to, 
        const vector<int>& nums,
        const vector<char>& ops, 
        unordered_map<int, vector<int>>& cache){

        if(from == to) return { nums[from] };

        if(from+1 == to) return { eval(nums[from], nums[to], ops[from]) };

        auto key = from*100+to;
        if(cache.count(key)) return cache[key];

        vector<int> ways;
        for(int i = from; i<=to-1; ++i){
            auto lefts = diffWaysToCompute(from, i, nums, ops, cache);
            auto rights = diffWaysToCompute(i+1, to, nums, ops, cache);

            for(auto left : lefts){
                for(auto right : rights){
                    ways.push_back(eval(left, right, ops[i]));
                }
            }
        }
        return  cache[key] = ways;
    }
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> ways;
        std::stringstream ss(expression);
        vector<int> nums;
        vector<char> ops;
        int num;
        while(ss>>num){
            nums.push_back(num);
            char op;
            if(ss>>op) ops.push_back(op);
        }   
        //assert(op.size()+1 == nums.size());

        unordered_map<int, vector<int>> cache;
        return diffWaysToCompute(0, nums.size()-1, nums, ops, cache);
    }
};
