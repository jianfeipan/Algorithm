class MyCalendar {
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) 
    {
        if(events.count(start)) return false;
        
        auto inserted = events.insert({start, end});
        auto nextEvent = next(inserted.first);
        if(nextEvent!=events.end())
        {
            if(end > nextEvent->first)
            {
                events.erase(start);
                return false;
            }
        }
        
        if(inserted.first!=events.begin())
        {
            auto previousEvent = prev(inserted.first);
            if(start < previousEvent->second)
            {
                events.erase(start);
                return false;
            }
        }
        return true;
    }
    
private:
    map<int, int> events;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
