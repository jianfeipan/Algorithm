/*Greatest Common Divisor Traversal

You are given a 0-indexed integer array nums,
and you are allowed to traverse between its indices.
You can traverse between index i and index j, i != j,
if and only if gcd(nums[i], nums[j]) > 1,
where gcd is the greatest common divisor.

Your task is to determine if for every pair of indices i and j in nums,
where i < j, there exists a sequence of traversals that can take us from i to j.

Return true if it is possible to traverse between all such pairs of indices,
or false otherwise.

Example 1:

Input: nums = [4,3,12]

Output: true
Explanation: There exists three possible pairsof indices.
For each pair, the sequence of traversals are:

(0,1) -> [0,2,1]
(0,2) -> [0,2]
(1,2) -> [1,2]

Example 2:

Input: nums = [2,3,7]

Output: false
Constraints:

1 <= nums.length <= 100,000
1 <= nums[i] <= 100,000

*/
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank_;

    UnionFind(int n) : parent(n), rank_(n, 0) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x){
        while(parent[x] != x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int a, int b){
        a = find(a); b = find(b);
        if(a == b) return;
        if(rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if(rank_[a] == rank_[b]) rank_[a]++;
    }
};

class Solution {
private:
    int gcd(int a, int b){
        while(b){
            a %= b;
            swap(a, b);
        }
        return a;
    }
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return true;

        UnionFind uf(n);

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(gcd(nums[i], nums[j]) > 1)
                    uf.unite(i, j);
            }
        }

        int root = uf.find(0);
        for(int i = 1; i < n; i++){
            if(uf.find(i) != root) return false;
        }
        return true;
    }
};

