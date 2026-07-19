class UnionFind
{
public:
    UnionFind(size_t size):
        _root(size, 0),
        _rank(size, 1)
    {
        for(int i=0; i<size; ++i) _root[i] = i;
    }
    
    unordered_map<int, set<int>> findIndexGroups(const vector<vector<int>>& pairs)
    {
        
        for(const auto & edge : pairs) merge(edge[0], edge[1]);

        unordered_map<int, set<int>> groupes;

        for(int i=0; i<_root.size(); ++i)
        {
            groupes[find(i)].insert(i);
        }
        
        return groupes;
    }
private:
    int find(int num)
    {
        if(num == _root[num]) return num;
        else return _root[num] = find(_root[num]);
    }
    
    void merge(int left, int right)
    {
        int leftRoot = find(left);
        int rightRoot = find(right);
        
        if(leftRoot != rightRoot)
        {
            if(_rank[left] > _rank[right])
            {
                _root[rightRoot] = leftRoot;
            }
            else if(_rank[left] < _rank[right])
            {
                 _root[leftRoot] = rightRoot;
            }
            else
            {
                _root[leftRoot] = rightRoot;
                ++_rank[leftRoot];
            }
        }
    }
    
private:
    vector<int> _root;
    vector<int> _rank;

};




class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) 
    {
        //union the indexes to see which are the blocks we can put any ordder of the letters
        UnionFind unionFind(s.size());
        unordered_map<int, set<int>> groupes = unionFind.findIndexGroups(pairs);
        
        string excangedStr = s;
        for(const auto & groupe : groupes)
        {
            multiset<char> charInorder;
            for(int index : groupe.second)
            {
                charInorder.insert(s[index]);
            }
            
            auto it = charInorder.begin();
            for(int index : groupe.second)
            {
                excangedStr[index] = *it;
                ++it;
            }
            
        }
        return excangedStr;
                
    }
};
