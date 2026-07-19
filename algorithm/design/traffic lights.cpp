#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>
#include <unordered_set>
#include <stdexcept>

using namespace std;

/*

Traffic lights
*/


class TrafficLightsController
{

enum class Color{green, yellow, red};

public:
    TrafficLightsController():this(60)
    {}
    
    TrafficLightsController(int period):
    _period(period),
    _current(0),
    _lights()
    {
        _lights = vector<Color>({
            {Color::green},
            {Color::red},
            {Color::green},
            {Color::red}
            });
    }
    
    vector<Color> & getLights()
    {
        return _lights;
    }
    
    void clock()
    {
        ++_current;
        if( _current == _period - 5)
        {

            swtichLightsToYellow(_lights);
        }
        else if( _current == _period)
        {
            swapLights(_lights);
            _current = 0;
        }
    }
    
private:
    void swtichLightsToYellow(vector<Color> & lights)
    {
        for(auto & light: lights)
            if(light == Color::green) light = Color::yellow;
    }

    void swapLights(vector<Color> & lights )
    {
        for(auto & light: lights)
            if(light == Color::yellow) light = Color::red;
            else light = Color::green;
    }
    
private:
    int _period;
    int _current;
    vector<Color> _lights;

    
};



int main(int argc, char *argv[])
{
   
   
   return 0;
}
