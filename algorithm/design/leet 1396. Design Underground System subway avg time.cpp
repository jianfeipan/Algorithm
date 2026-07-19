class UndergroundSystem {
public:
    UndergroundSystem():_sumAndCount(), _checkIn()
    {
        
    }
    
    void checkIn(int id, string stationName, int t) 
    {
        _checkIn[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) 
    {
        const int rideTime = t - _checkIn[id].second;
        auto & sumAndCount  =  _sumAndCount[_checkIn[id].first][stationName];
        sumAndCount.first+=rideTime;
        ++sumAndCount.second;
        _checkIn.erase(id);
    }
    
    double getAverageTime(string startStation, string endStation) //const
    {
        if(!_sumAndCount.count(startStation) ||  !_sumAndCount[startStation].count(endStation)) 
            throw invalid_argument("no recode for "+startStation+" - "+endStation);
        
        const auto & sumAndCount  =  _sumAndCount[startStation][endStation];
        return (double)sumAndCount.first/sumAndCount.second;
    }
    
private:
    using TotalTime = int;
    using RideCount = size_t;
    using RideMetric = pair<TotalTime, RideCount>;
    using Destimations = unordered_map<string, RideMetric>;
    
    unordered_map<string, Destimations> _sumAndCount;
    unordered_map<int, pair<string, int>> _checkIn;
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
