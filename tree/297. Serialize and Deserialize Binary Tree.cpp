/*

Implement an algorithm to serialize and deserialize a binary tree.

Serialization is the process of converting an in-memory structure into a sequence of bits so that it can be stored or sent across a network to be reconstructed later in another computer environment.

You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure. There is no additional restriction on how your serialization/deserialization algorithm should work.

Note: The input/output format in the examples is the same as how NeetCode serializes a binary tree. You do not necessarily need to follow this format.

Example 1:



Input: root = [1,2,3,null,null,4,5]

Output: [1,2,3,null,null,4,5]
Example 2:

Input: root = []

Output: []
Constraints:

0 <= The number of nodes in the tree <= 1000.
-1000 <= Node.val <= 1000


*/

class Codec {

private:
    void serialize(TreeNode* root, string& serialized) {
        if(!root) serialized+="N ";
        else {
            serialized+=to_string(root->val)+" ";
            serialize(root->left, serialized);
            serialize(root->right, serialized);
        }
    }

    TreeNode* deserialize(const vector<string> & tokens, int &pos){
        if(pos>=tokens.size()) return nullptr;
        if(tokens[pos]=="N") 
        {
            ++pos;
            return nullptr;
        }
        TreeNode *node = new TreeNode(stoi(tokens[pos]));
        ++pos;
        node->left = deserialize(tokens, pos); 
        node->right = deserialize(tokens, pos); 
        
        return node;
    }

    vector<string> split(const string& s) {
        vector<string> result;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            result.push_back(word);
        }
        return result;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serialized;
        serialize(root, serialized);
        return serialized;  
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        auto tokens = split(data);
        int pos = 0;
        return deserialize(tokens, pos);

    }
};
