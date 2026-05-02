/*
circle detection: do the iteration of prerequisites, 

*/
class Solution {// typological sort
public:
    vector<int> canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> post_request(numCourses);
        vector<int> prereq_cout(numCourses);

        for(int i=0; i<prerequisites.size(); ++i){
            auto postreq = prerequisites[i][0];
            auto prereq = prerequisites[i][1];

            post_request[prereq].push_back(postreq);
            ++prereq_cout[postreq];
        } 

        queue<int> to_process;
        for(int t = 0; t<numCourses; ++t) if(0 == prereq_cout[t]) to_process.push(t);
        
        unordered_set<int> processed;
        vector<int> order;
        while(!to_process.empty()){
            auto cur = to_process.front(); to_process.pop();
            processed.insert(cur);
            order.push_back(cur);

            for(auto next : post_request[cur]){
                --prereq_cout[next];
                if(prereq_cout[next] == 0) to_process.push(next);
            }
        }

        return order.size() == numCourses ? order : vector<int>();
    }
};
