class Solution {
private:
    template<typename Op>
    void applyOperation(stack<int> & nums, Op op){
        auto right = nums.top();
        nums.pop();
        auto left = nums.top();
        nums.pop();
        nums.push(op(left,right));
    }


public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for(const auto & token:tokens){
            if(token=="+"){
                applyOperation(nums, [](int left, int right){ return left+right;});

            }else if(token=="-"){
                applyOperation(nums, [](int left, int right){ return left-right;});

            }else if(token=="*"){
                applyOperation(nums, [](int left, int right){ return left*right;});

            }else if(token=="/"){
                applyOperation(nums, [](int left, int right){ /*right!=0 check*/return left/right;});
            }else{
                nums.push(stoi(token));
            }
        }
        return nums.top();
    }
};
