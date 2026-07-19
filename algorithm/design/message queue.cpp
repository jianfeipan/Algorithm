#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <map>
#include <queue>

using namespace std;

/*
Given (1, “aaa”) (2, “bbb”) (3, “ccc”) (4, “ddd”) (5, “eee”),
1. pass in 1, 输出 “aaa"
2. pass in 3, 不输出任何str，因为跳过了2
3. pass in 2, 输出 “bbb”,“ ccc”
*/

class MessageQueue
{
public:
    void push(int id, const string & msg)    
    {
        _msgs.push({id, msg});
    }
    
    string read(int id)
    {
        _readRequests.insert(id);
        
        string repsonse;
        
        while(!_readRequests.empty() && !_msgs.empty() && _readRequests.count(_msgs.front().first))
        {
            repsonse+=" ";
            repsonse+=_msgs.front().second;
            _readRequests.erase(_msgs.front().first);_msgs.pop();
            
        }
        return repsonse;
    }
    
private:
    queue<pair<int, string>> _msgs;
    unordered_set<int> _readRequests;

};

int main(int argc, char *argv[])
{
    MessageQueue mq;
    mq.push(1,"aaa");
    mq.push(2,"bbb");
    mq.push(3,"ccc");
    mq.push(4,"ddd");
    mq.push(5,"eee");
    
    cout<<mq.read(1)<<endl;
    cout<<mq.read(3)<<endl;
    cout<<mq.read(4)<<endl;
    cout<<mq.read(2)<<endl;
    cout<<mq.read(5)<<endl;
    
    
    return 0;
}



#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>
#include <list>
#include <set>
#include <map>
#include <array>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Reorder Packets
There is a continous stream of data in the form of (1, "abcd"). Write a program to output the data from the stream in realtime in order, so 1,2,3,4,5. You cannot queue up the incoming data from the stream.
Input: (1, "abcd"), (2, "efgh"), (4, "mnop"), (5, "qrst"), (3, "ijkl")
So for example if the first incoming bit of data is (1, "abcd"), and the second is (4, "mnop"), you cannot output (4, "mnop") until you get 2, 3.


*/

class MassageQueue
{
public:    
MassageQueue():_queue(), _waitFor(1)
{
    
}
    
public:
    vector<pair<int, string>> send(int order, const string & msg)
    {
        vector<pair<int, string>> outputs;
        if(_waitFor == order)
        {
            outputs.push_back({order, msg});
            
            auto it = _queue.find(++_waitFor);
            while(it!=_queue.end())
            {
                outputs.push_back(*it);
                it = _queue.find(++_waitFor);
            }
        }
        else
        {
            _queue[order] = msg;
        }
        return outputs;
    }
    
private:
    map<int, string> _queue;
    int _waitFor;
    

};

void sendMsg(MassageQueue & q,int order, const string & msg)
{
    const auto & outputs = q.send(order, msg);
    for(const auto & output : outputs) cout<<output.first << " : "<< output.second<<" ";
    cout<<endl;
}

int main()
{
    MassageQueue q;
    sendMsg(q, 1, "aa");
    sendMsg(q,4, "dd");
    sendMsg(q,2, "bb");
    sendMsg(q,3, "cc");
    sendMsg(q,6, "ff");
    sendMsg(q,7, "ff");
    sendMsg(q,8, "ff");
    sendMsg(q,5, "ff");

    
}
