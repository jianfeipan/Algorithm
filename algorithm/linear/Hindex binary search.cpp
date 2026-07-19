

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*
Given an array citations[] consisting of N integers in non-increasing order, representing citations, the task is to find the H-index.

H-Index is usually assigned to the researcher denoting the contributions made in terms of no of papers and citations. H-index(H) is the largest value such that the researcher has at least H papers cited at least H times.

Examples:

Input: citations[] = {5, 3, 3, 0, 0} 
Output: 3 
Explanation: 
There are atleast 3 papers (5, 3, 3) with atleast 3 citations
Input: citations[] = {5, 4, 2, 1, 1} 
Output: 2 
Explanation: 
There are atleast 2 papers (5, 4, 2) with atleast 2 citations.
*/

int findHindex(vector<int> prices) 
{
    sort(prices.begin(), prices.end(), greater<int>());
    int hindex = 0;
    
    //from big to small : the task is find the last one which is bigger than index +1
    
    int left = 0;
    int right = prices.size()-1;
    
    while(left<=right)
    {
        int mid = (left+right)>>1;
        if(prices[mid] >= mid +1)//mid is on the left side,next iteration we go two current's right
        {
            hindex = mid+1;
            left = mid+1;
        }
        else //mid is on the right side,next iteration we go two current's left
        {
            right = mid-1;
        }
    }
    
    
    return hindex;
}



int main(int argc, char *argv[])
{
    cout<<findHindex({5, 3, 3, 0, 0});
    return 0;
}

