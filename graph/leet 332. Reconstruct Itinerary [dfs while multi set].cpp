#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;

class Solution {
public:

vector<string> findItinerary(vector<vector<string>>& tickets)
{
   unordered_map<string, multiset<string>> outComes;
   vector<string> route;
   for (const auto & ticket : tickets)  outComes[ticket[0]].insert(ticket[1]);

   // Iterative Hierholzer's: explicit stack replaces recursion
   stack<string> stk;
   stk.push("JFK");
   while (!stk.empty()) {
      string& current = stk.top();
      if (outComes[current].size()) {// this still need to fly somewhere, to the stack
         auto first = outComes[current].begin();
         string next = *first;
         outComes[current].erase(first);
         stk.push(next);
      } else {// who don't have next,, it's the end, push_back and pop it
         route.push_back(current);
         stk.pop();
      }
   }
   return vector<string>(route.rbegin(), route.rend());
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
