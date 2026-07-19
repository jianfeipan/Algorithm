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

    Node* clone(Node* org) {
        if (!org) return nullptr;
        if (org_copy.count(org)) return org_copy[org];

        Node* copy = new Node(org->val);
        org_copy[org] = copy;
        copy->neighbors.reserve(org->neighbors.size());
        for (auto* nei : org->neighbors) {
            copy->neighbors.push_back(clone(nei));
        }

        return copy;
    }

public:
    Node* cloneGraph(Node* node) {
        org_copy.clear();
        return clone(node);
    }
};


