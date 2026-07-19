

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include <unordered_set>
#include <stdexcept>
#include <deque>

using namespace std;

/*
Campany stock trade volume
    - we receive a stream of <company, tradeVolum> , return the top K traded company --> top k map + vector
    -
    
*/

class TopKTraded
{
public :

    TopKTraded(size_t k):_k(k), _volumesAndIndexes(), _topK(){ _topK.reserve(_k+1);} 
    
    void record(const string & company, size_t volume)//O(1) + O(K)
    {
        if(!_volumesAndIndexes.count(company))
            _volumesAndIndexes[company] = {volume, -1};
        else
            _volumesAndIndexes[company].first+=volume;
        
        if(-1 == _volumesAndIndexes[company].second)//company not in topy k for now
        {
            _volumesAndIndexes[company].second = _topK.size();
            _topK.push_back(company);
        }
        
        for(int current = _volumesAndIndexes[company].second; current>= 1; --current)
        {
            if(_volumesAndIndexes[_topK[current - 1]].first < _volumesAndIndexes[_topK[current]].first )
            {
                
                //cout<< "swap : "<<_topK[current - 1]<<":"<< _volumesAndIndexes[_topK[current - 1]].first << ", "<<_topK[current]<< ":" << _volumesAndIndexes[_topK[current]].first <<endl;
                auto temp = _topK[current - 1];
                _topK[current - 1] = _topK[current];
                _topK[current] = temp;
                
                _volumesAndIndexes[_topK[current - 1]].second = current - 1;
                _volumesAndIndexes[_topK[current]].second = current;
            }
            else break;
        }
        
        if(_topK.size() > _k)
        {
            _volumesAndIndexes[_topK.back()].second = -1;
            _topK.pop_back();
        }
    }
    
    void printTopK()
    {
        for(const auto & company : _topK) cout<<company<<" ,";
        cout<<endl;
    }
    
private:
    size_t _k;
    unordered_map<string, pair<size_t, int>> _volumesAndIndexes;
    vector<string> _topK;
};


int main(int argc, char *argv[])
{
    TopKTraded top(3);
    
    top.record("a", 100);top.printTopK();
    top.record("b", 200);top.printTopK();
    top.record("a", 100);top.printTopK();
    top.record("a", 100);top.printTopK();
    top.record("c", 400);top.printTopK();
    top.record("d", 700);top.printTopK();
    top.record("e", 600);top.printTopK();
    
    
    
    return 0;
}
