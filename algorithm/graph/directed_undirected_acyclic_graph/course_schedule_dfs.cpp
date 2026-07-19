class Solution {

private:
    bool has_circle(int from, 
                    const vector<unordered_set<int>>& prerequest,
                    vector<char>& current_path,
                    vector<char>& visited) {
        if (visited[from]) return false;
        if (current_path[from]) return true;// back edge!

        current_path[from] = true;
        for (const auto& next : prerequest[from]) {
            if(has_circle(next, prerequest, current_path, visited)) return true;
        }
        current_path[from] = false; // backtracing

        visited[from] = true;
        return false;
    };    
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<unordered_set<int>> prerequest(numCourses);

        for (const auto& prereq : prerequisites) {
            prerequest[prereq[0]].insert(prereq[1]);
        }
        // dfs cirle detection
        vector<char> visited(numCourses, false); // vector<bool> is bit...slow

        for (int from = 0; from < numCourses; ++from) {
            if(!visited[from]) {
                vector<char> current_path(numCourses, false);
                if(has_circle(from, prerequest, current_path, visited)) return false;
            }
        }
        return true;
    }
};
