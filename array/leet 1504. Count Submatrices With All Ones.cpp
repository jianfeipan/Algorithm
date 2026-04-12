/*
[
    [1, 1,1],
    [1,>1,0],
    [1, 1,0]
]

loop (r,c): sum += numbers with (r, c) as the right bottom corner: every new node add new different matrices
    -> numbers with (r, c)  is numbers of all 1s formed by the left top corner.
                                        0    1   2 3  4  5
        -> how many ones looking up, [ 2(1) 2(1) 1 2  5 >3 ]  represent now many consecutive 1s above
                                                         c
        -> if i have right bottom corner at index 5,
            -> index 5: height 3 can extend width 1: 3*1
            -> index 4: height 2 can extend width 3: 2*3
            -> index 3 skipped
            -> index 2: height 1 can extend width 6: 1*6
            -> index 0, 1 skipped
        -> monoton stack: increasing: knowing where do the current height stops to left
        -> dp:if I know how many matrics on end1, so for end2 = end1+(more matrix [end1+1, end2])

we are going to count the right bottom corner: 
    - simplify it to " row by row hostogram"  
    - make use of the monoton stack to find how the current height extends to lft 
*/
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        const auto& R = mat.size(); if(R==0) return 0;
        const auto& C = mat[0].size(); if(C==0) return 0;

        int sum = 0;
        vector<int> hist(C, 0);
        for(int r=0; r<R; ++r){
            //for each row: find the consecutive 1s looking up
            for(int c=0; c<C; ++c){
                if(mat[r][c]==0) hist[c] = 0;
                else hist[c]+=1;
            }

            // check each point as right bottom corner monoton stack to check how far we can go to the left
            stack<int> increasing;
            vector<int> rowSum(C, 0);
            for(int c=0; c<C; ++c){
                // right bottom is [r,c]
                auto currentHeight= hist[c];
                while(!increasing.empty() && hist[increasing.top()]>=currentHeight) increasing.pop();
                if(!increasing.empty()){
                    auto leftSmallerIndex = increasing.top();
                    rowSum[c]= rowSum[leftSmallerIndex] + currentHeight*(c - leftSmallerIndex); 
                    // rowSum[leftSmallerIndex] is a DP thinking: from a previous c, i just have all them add here.
                }else{
                    rowSum[c]= currentHeight*(c + 1);          
                }
                increasing.push(c);
                sum+=rowSum[c];
            }
        }
        return sum;
    }
};
