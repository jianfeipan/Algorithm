/*
1104. Path In Zigzag Labelled Binary Tree
Medium
1.4K
299
Companies
In an infinite binary tree where every node has two children, the nodes are labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.

Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.

 

Example 1:

Input: label = 14
Output: [1,3,4,14]
Example 2:

Input: label = 26
Output: [1,2,6,10,26]

*/

class Solution {

    /*
    fact:
        level 0: 2^0
        level 1: 2^1, 2^2 -1
        level 2: 2^2, 2^3 -1
        ...

    idea:
        first, let's think always labeling from left:
        give n: n = 2^k +c
        k gives the level, and c gives the index

        14 = 2^3 +6
        7,3,1

        path is 14/2 = 7,
                7/2 = 3,
                3/2 =1
    */
public:
    vector<int> pathInZigZagTree(int label) {

        vector<int> path;//[14,7,3,1]

        while(label>0)
        {
            path.push_back(label);
            label/=2;
        } 

        vector<int> res(path.rbegin(), path.rend());//reverse [1,3,7,14]

        for(int i = res.size()-2; i>0; i-=2)//no matter from left or from right, n-1 and n-2 is in different order, so you need to "fix" the number every two level. and the way to fix that is what ever it is, you need to inverse to the mirror position, the formular is: we are on level k, we have current x, the mirror number is 2^k + (2^k - (x - 2^k) - 1 )
        {
            res[i] = 3*pow(2,i) - res[i] -1;
        }


        return res;





    }
};
