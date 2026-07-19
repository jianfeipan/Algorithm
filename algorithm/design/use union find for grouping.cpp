class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) 
    {
        _root = vector<int>(isConnected.size(), 0);
        for(int i = 0; i<_root.size(); ++i) _root[i] = i;
        
        for(int from = 0; from < isConnected.size(); ++from)
        {
            for(int to = from+1; to < isConnected[from].size(); ++to)
            {
                if(isConnected[from][to])
                    unionElements(from ,to);
            }
        }
        
        
        unordered_set<int> unique;
        for(int i = 0; i<_root.size(); ++i)
        {
            cout<<_root[i]<<endl;
            unique.insert(find(i));
        }
        
        return unique.size();
    }
    
private:
    int find(int num)
    {
        if(_root[num] == num) return num;
        else return _root[num] = find(_root[num]); //recusive to update!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    
    void unionElements(int left, int right)
    {
        int leftRoot = find(left);
        int rightRoot = find(right);
        
        if(leftRoot!=rightRoot)
        {
            _root[leftRoot] = rightRoot;//union the root of root !!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }
    
private:
    vector<int> _root;
    vector<int> _rank;
};
