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

struct Node
{
    Node(int value):val(value), left(nullptr), right(nullptr){}
    
    int val;
    Node * left;
    Node * right;
};

static void closestNode_recutive(  Node *  root, int num,
                            Node* & maxLeftNode, int &  maxLeft,
                            Node* & minRightNode, int & minRight)
{
    
    if(root)
    {
       
        if(root->val < num) 
        {
            maxLeftNode = root;
            maxLeft = root->val;
            
            closestNode_recutive(root->right, num, maxLeftNode, maxLeft, minRightNode, minRight);
        }
        else
        {
            minRightNode = root;
            minRight = root->val;
            
            closestNode_recutive(root->left, num, maxLeftNode, maxLeft, minRightNode, minRight);            
        }
    }
}


Node * cloestNode(Node * root, int num)
{
    int maxLeft = INT_MIN;
    int minRight = INT_MAX;
    
    Node * maxLeftNode = root;
    Node * minRightNode = root;
    
    closestNode_recutive(root, num, maxLeftNode, maxLeft, minRightNode, minRight);

    return abs(num - maxLeft) < abs(minRight - num) ?  maxLeftNode : minRightNode;
}

int main()
{
    Node node10(10);
    Node node20(20);
    Node node30(30);
    Node node40(40);
    Node node50(50);
    Node node60(60);
    
    node20.left = &node10;
    node20.right = &node30;
    
    node40.left = &node20;
    node40.right = &node50;
    node50.right = &node60;
    
    auto found = cloestNode(&node40, 51);cout<< found->val<<endl;
    
    found = cloestNode(&node40, 41);cout<< found->val<<endl;
    found = cloestNode(&node40, 49);cout<< found->val<<endl;
    found = cloestNode(&node40, 19);cout<< found->val<<endl;
    found = cloestNode(&node40, 11);cout<< found->val<<endl;


    return 0;
}
