#include <stdio.h>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

pair<int, int> findTop2(const vector<int> & nums)
{
    int top1 = -1;
    int top2 = -1;
    
    for(int num : nums)
    {
        top2 = max(top2, min(top1, num));
        top1 = max(top1, num);
    }
    
    cout<< top1<<","<<top2<<endl;
    
    return {top1, top2};
}


int main()
{
    
    findTop2({1,2,3,4,5,6,7,8});
    findTop2({1,2,3,4,5,6,7,8,123,45,4,5,7});
    return 0;
}
