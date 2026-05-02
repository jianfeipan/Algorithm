/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> levels;
        
        //BFS
        
        queue<Node*> queue;
        if(root)
            queue.push(root);
        
        while(!queue.empty())
        {
            const size_t levelSize = queue.size();
            vector<int> level;
            level.reserve(levelSize);
            
            for(size_t i = 0; i< levelSize; ++i)
            {
                const Node * current = queue.front();
                level.push_back(current->val);
                queue.pop();
                for(Node * child : current-> children)
                {
                    if(child)
                        queue.push(child);
                }
            }
            
            levels.push_back(level);
            
        }
        
        return levels;
        
    }
};
