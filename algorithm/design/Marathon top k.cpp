

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*
runner - chckpoint
*/

struct Runner{
    int id;
    string name;
};

struct ChecckPoint
{
    int id;
    double distanceLeft;  
};

class Marathon
{
public:
    Marathon(size_t k):_k(k), _runners(), _checkPoints(), _runnerPositionRank(),_topK(){
        _topK.reserve(_k);
    }
    
    void checkIn(const Runner & runner)
    {
        _runners[runner.id] = runner.name;
    }
    
    void setUp(const ChecckPoint & checkPoint)
    {
        _checkPoints[checkPoint.id] = checkPoint.distanceLeft;
    }

    void check(int runnerId, int checkPointId)
    {
        cout<<"comes: "<<_runners[runnerId]<< ":"<< _checkPoints[checkPointId] <<endl;
        if(!_runnerPositionRank.count(runnerId))
        {
            _runnerPositionRank[runnerId] = {checkPointId,-1};
        }
        else
        {
            _runnerPositionRank[runnerId].first = checkPointId;
        }
        
        if(_runnerPositionRank[runnerId].second == -1)
        {
             _runnerPositionRank[runnerId].second = _topK.size();
            _topK.push_back(runnerId);
            cout<<" size :"<<_topK.size() <<endl;

        }
        
        for(int currentRunnerIndex = _runnerPositionRank[runnerId].second; currentRunnerIndex>=1; --currentRunnerIndex)
        {
            const int prevRunnerIndex = currentRunnerIndex-1;
            const int prevRunnerId = _topK[prevRunnerIndex];
            const int prevRunnerPos = _checkPoints[_runnerPositionRank[prevRunnerId].first];
            const int currentRunnerPos = _checkPoints[_runnerPositionRank[runnerId].first];
            
            if(prevRunnerPos > currentRunnerPos)
            {
                auto temp = _topK[prevRunnerIndex];
                _topK[prevRunnerIndex] = _topK[currentRunnerIndex];
                _topK[currentRunnerIndex] = temp;
                
                _runnerPositionRank[prevRunnerId].second = currentRunnerIndex;
                _runnerPositionRank[runnerId].second = prevRunnerIndex;
                
                cout<<"swap : "<< _runners[runnerId] << _runners[prevRunnerId]<<endl;
            }
            else break;
        }
        
        if(_topK.size() >_k)
        {
            _runnerPositionRank[_topK.back()].second = -1;
            _topK.pop_back();
        }

    }
    
    void printTopK()
    {
        for(int runnerID : _topK) cout<<_runners[runnerID]<<", ";
        cout<<endl;
    }
    
   
    
private:
    size_t _k;
    unordered_map<int, string> _runners;
    unordered_map<int, int> _checkPoints;
    
    
    unordered_map<int, pair<int, int>> _runnerPositionRank;
    vector<int> _topK;
    
};



int main(int argc, char *argv[])
{
    Marathon marathon(3);
    
    marathon.checkIn({1, "a"});
    marathon.checkIn({2, "b"});
    marathon.checkIn({3, "c"});
    marathon.checkIn({4, "d"});
    marathon.checkIn({5, "e"});
    marathon.checkIn({6, "f"});
    marathon.checkIn({7, "g"});
    marathon.checkIn({8, "h"});
    
    marathon.setUp({1, 100});
    marathon.setUp({2, 80});
    marathon.setUp({3, 75});
    marathon.setUp({4, 60});
    marathon.setUp({5, 50});
    marathon.setUp({6, 30});
    marathon.setUp({7, 20});
    marathon.setUp({8, 10});
    
    
    marathon.check(2, 1);marathon.printTopK();
    marathon.check(2, 2);marathon.printTopK();
    marathon.check(1, 1);marathon.printTopK();
    marathon.check(1, 2);marathon.printTopK();
    marathon.check(2, 3);marathon.printTopK();
    marathon.check(3, 1);marathon.printTopK();
    marathon.check(3, 2);marathon.printTopK();
    marathon.check(3, 3);marathon.printTopK();
    marathon.check(4, 4);marathon.printTopK();
    marathon.check(5, 6);marathon.printTopK();
    marathon.check(7, 7);marathon.printTopK();
    marathon.check(8, 7);marathon.printTopK();
    
    return 0;
}
