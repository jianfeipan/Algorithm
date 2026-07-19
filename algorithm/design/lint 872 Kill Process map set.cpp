class Solution {
public:
    /**
     * @param pid: the process id
     * @param ppid: the parent process id
     * @param kill: a PID you want to kill
     * @return: a list of PIDs of processes that will be killed in the end
     */
    vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill) 
    {
        unordered_map<int, unordered_set<int>> processTree;

        for(int i = 0; i< ppid.size(); ++i)
        {
            processTree[ppid[i]].insert(pid[i]);
        }
        vector<int> killPid;

        kill_dfs(kill, processTree, killPid);

        return killPid;
    }

    void kill_dfs(int toKill, const unordered_map<int, unordered_set<int>> & processTree, vector<int> & killPid)
    {
        auto it = processTree.find(toKill);
        if(it!=processTree.end())
        {
            for(const auto & pid : it->second) kill_dfs(pid, processTree, killPid);   
        }
        killPid.push_back(toKill);
    }
};
