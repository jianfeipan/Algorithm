
class Solution {// dfs
private:
    bool dfs_has_circle(
        int current, 
        vector<int>& tested, //tested → memoization (“this subtree is safe”)
        vector<int>& current_path, ////circle detection (“this node is in current path”)
        const vector<vector<int>>& post_request){
        
        current_path[current] = 1;
        for(auto next : post_request[current]){
            if(current_path[next]) return true;

            if(!tested[next]){ // this node is test and no circle
                if(dfs_has_circle(next, tested, current_path,post_request)) return true;
            }
        }
        current_path[current] = 0;

        tested[current] = 1;// tested: no circle
        return false;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> post_request(numCourses);
        for(int i=0; i<prerequisites.size(); ++i){
            auto postreq = prerequisites[i][0];
            auto prereq = prerequisites[i][1];

            post_request[prereq].push_back(postreq);
        } 

        vector<int> tested(numCourses);
        for(int i=0; i<numCourses; ++i){
            if(!tested[i]){
                vector<int> current_path(numCourses);
                if(dfs_has_circle(i, tested, current_path, post_request)) return false;
            }
        } 

        return true;
    }
};
