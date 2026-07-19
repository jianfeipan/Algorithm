

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

vector<vector<int>> rotateLeftMatrix(vector<vector<int>> matrix) 
{
    
    /*
    rotate left is exactly diaconal miror by [i][j] -> [j][i] then updown mirror : [i][j] = [i][size-j]
    
    or by left right mirror then diaconal mirror
    
    */
    vector<vector<int>> rotated(matrix[0].size(), vector<int>(matrix.size(), 0));
    
    for(size_t lin = 0; lin<matrix.size(); ++lin)
    {
        for(size_t col = 0; col<matrix[lin].size(); ++col)
        {
            rotated[col][lin] = matrix[lin][col];
        }
    }
    
    reverse(rotated.begin(),rotated.end());

    return rotated;
}



int main(int argc, char *argv[])
{
    auto rotated = rotateLeftMatrix({
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10,11,12}
    });
    
    for(auto & line : rotated)
    {
        for(auto & num : line) cout<<num<<" ";
        cout<<endl;
    }
    cout<<endl;
    return 0;
}
