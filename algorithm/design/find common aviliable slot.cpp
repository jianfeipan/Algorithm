#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <optional>
#include <utility>
#include <climits>

using namespace std;

/*
members have different avilable slots, find the first common avilable slot


*/

class TeamAvilibilities
{
public:
    using Slot = pair<int, int>;
    using Avilibilites = vector<Slot>;
    
    TeamAvilibilities() = default;
    
    void addPeopleAvilibilites(const Avilibilites & avilibilites)
    {
        _memberAvilibilites.emplace_back(avilibilites);
    }
    
    void addPeopleAvilibilites(Avilibilites && avilibilites)
    {
        _memberAvilibilites.emplace_back(avilibilites);
    }
    
    optional<Slot> findAvilableSlot() const
    {
        /*
        idea: use a vectoe for indexes, start from 0, then move the min left index
        */
        optional<Slot> slot;
        
        vector<size_t> currentIndexes(_memberAvilibilites.size(), 0); 
        
        bool continueSeaching = true;
        while(continueSeaching/*all index <  it's Avilibilitess size*/)
        {
            size_t minEndMember = 0;
            int maxStart = INT_MIN;
            int minEnd = INT_MAX;
            
            for(size_t m = 0; m<_memberAvilibilites.size(); ++m)
            {
                auto currentIndex = currentIndexes[m];
                auto currentStart = _memberAvilibilites[m][currentIndex].first;
                auto currentEnd = _memberAvilibilites[m][currentIndex].second;
                
                maxStart = max(maxStart, currentStart);
                
                if(currentEnd < minEnd)
                {
                    minEnd = currentEnd;
                    minEndMember = m;
                }
            }
            
            if(maxStart <= minEnd)//close slot our open
            {
                slot = {maxStart, minEnd};
                continueSeaching = false;
            }
            else
                if(++currentIndexes[minEndMember] >= _memberAvilibilites[minEndMember].size()) continueSeaching=false;;
        }
        
        return slot;
    }    

private:
    vector<Avilibilites> _memberAvilibilites;
    
};

void test(const TeamAvilibilities & team)
{
    auto slot = team.findAvilableSlot();
    if(slot)
        cout<< "find slot: "<<slot->first  <<", "<< slot->second <<endl;
    else
        cout<< "no aviliable slot was found!"<<endl;
}


TeamAvilibilities happy_path()
{
    TeamAvilibilities team;
    
    team.addPeopleAvilibilites({{1,     3},     {5,      7},     {9,10}});
    team.addPeopleAvilibilites({            {4,     6},         {9,10}});
    team.addPeopleAvilibilites({   {2,          5},         {8, 9}, {10,11}});
    
    return team;
}


TeamAvilibilities not_found()
{
    TeamAvilibilities team;
    
    team.addPeopleAvilibilites({{1,     3}});
    team.addPeopleAvilibilites({            {4,     6},         {9,10}});
    team.addPeopleAvilibilites({   {2,          5},         {8, 9}, {10,11}});
    
    return team;
}

int main()
{
    test(happy_path());
    test(not_found());
    return 0;
}
