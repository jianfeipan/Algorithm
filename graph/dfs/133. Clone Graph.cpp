/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
private:
    unordered_map<Node*, Node*> org_copy;
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;

        if(org_copy.count(node)) return org_copy[node];

        auto copy = new Node(node->val);
        org_copy[node] = copy;

        copy->neighbors.reserve(node->neighbors.size());
        for(auto neighbor : node->neighbors){
            copy->neighbors.push_back(cloneGraph(neighbor));
        }

        return copy;
    }
};

