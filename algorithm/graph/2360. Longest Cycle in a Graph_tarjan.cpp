class Solution {
private: 
    int _timer;
    unordered_map<int, unordered_set<int>> _edges;
    unordered_map<int, int> _visitedAt;
    unordered_map<int, int> _low;

    unordered_set<int> _currentPath;

    void _dfs(int from){
        ++_timer;
        _visitedAt[from] = _low[from]= _timer;
        _currentPath.insert(from);

        if(!_edges.count(from)) return;
        for(const auto& next : _edges[from]){

            if(!_visitedAt.count(next)){ // if next not visited
                _dfs(next);
                _low[from] = min(_low[from], _low[next]);// maybe next low was updated, back propagate to from
            }else{
                if(_currentPath.count(next)){ // if visited and in current dfs path: it's a back edge
                    _low[from] = min(_low[from], _low[next]);
                }
            }
        }
    }

public:
    int longestCycle(vector<int>& edges) {
        // tarjan
        _timer = 0;
        _edges.clear();
        _visitedAt.clear();
        _low.clear();
        // better Data Structure for handling multi out situation.
        for(int from = 0; from<edges.size(); ++from) _edges[from].insert(edges[from]);
        
        for(int from = 0; from<edges.size(); ++from){
            if(!_visitedAt.count(from)){
                _currentPath.clear();
                _dfs(from);
            } 
        }

        int longest=0;
        unordered_map<int, int> low_count;
        for(const auto& [ _, lowLinked] : _low){
            ++low_count[lowLinked];
            longest=max(longest, low_count[lowLinked]);
        }
        
        return longest == 1 ? -1 : longest;
    }
};
