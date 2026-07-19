#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> flights;
        for(auto& ticket : tickets) flights[ticket[0]].push_back(ticket[1]);

        stack<string> visiting;
        visiting.push("JFK");

        vector<string> path;
        while(!visiting.empty()){
            auto cur = visiting.top();
            if(flights[cur].empty()){ // no more tickets
                path.push_back(cur); // cur is the last station
                visiting.pop();
            }else{
                auto next = flights[cur].back();// next is a station before current
                visiting.push(next);
                flights[cur].pop_back();// consum ticket!!!!
            }
        }
        return vector<string>(path.rbegin(), path.rend());
    }
};

void printRoute(const vector<string>& route) {
   for (int i = 0; i < route.size(); i++) {
      if (i) cout << " -> ";
      cout << route[i];
   }
   cout << endl;
}

int main() {
   Solution sol;

   // Case 1: JFK->A, JFK->N, N->JFK => JFK -> N -> JFK -> A
   vector<vector<string>> tickets1 = {{"JFK","A"}, {"JFK","N"}, {"N","JFK"}};
   cout << "Case 1 (with A): ";
   printRoute(sol.findItinerary(tickets1));

   // Case 2: JFK->Z, JFK->N, N->JFK => JFK -> N -> JFK -> Z
   vector<vector<string>> tickets2 = {{"JFK","Z"}, {"JFK","N"}, {"N","JFK"}};
   cout << "Case 2 (with Z): ";
   printRoute(sol.findItinerary(tickets2));

   return 0;
}
