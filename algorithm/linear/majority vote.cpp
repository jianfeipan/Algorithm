#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

template<class T>
optional<T> majorityVote(const vector<T> & elements)
{
    optional<T> majority;
    if(!elements.empty())
    {
        T candidate = elements[0];
        size_t count = 1;
        for(const auto & e : elements)
        {
            if(count == 0)
            {
                candidate = e;
                count=1;
            }
            else 
            {
                if(e == candidate) ++count;
                else --count;
            }
        }
        
        count = 0;
        for(const auto & e : elements)
        {
            if(e == candidate) ++count;
        }
        
        if(count > elements.size()/2) majority = candidate;
    }
    return majority; 
}

int main()
{
    cout<< "inplace : "<<endl;
    vector<int> nums({2,1,2,1,2,1,2,1,1,1,2,1,2});
    
    auto m = majorityVote(nums);
    if(m) cout<<*(m)<<endl;
    else cout<<"no majority"<<endl;    
    return 0;
}
