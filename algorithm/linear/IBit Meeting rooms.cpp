int Solution::solve(vector<vector<int> > &A) 
{
    map<int, int> timeLine;
    for(const auto & meeting : A)
    {
        ++timeLine[meeting[0]];
        --timeLine[meeting[1]];
    }

    int need=0;
    int maxNeed = 0;
    for(const auto & [time, meeting]:timeLine)
    {
        need+=meeting;
        maxNeed = max(maxNeed, need);
    }

    return maxNeed;
}
