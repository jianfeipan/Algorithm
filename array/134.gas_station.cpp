class Solution {
private:
    bool startFrom(int i, int tank, int steps, vector<int>& gas, vector<int>& cost){
        if(steps == gas.size()) return true;

        tank += gas[i]; 
        tank -= cost[i];
        if(tank<0) return false;

        return startFrom((i+1)%gas.size(), tank, steps+1, gas, cost);
    }
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        vector
        for(int i=0; i<gas.size(); ++i){
            if(startFrom(i, 0, 0, gas, cost)) return i;
        }
        return -1;
    }
};


class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        /*
        try to find a start that can reach end,

        initialize  end to 0, 
                    start to n-1,
        try to check from current start if we can have a tank negative:
            if tank<0 try a earliler start start--
            if tank=> try go further :  end++

            when start meet end: we finished
                if tank < 0 : cannot do it.
                if tank < 
        */
        const auto& n = gas.size();
        int start = n-1;
        int end = 0;
        int tank = gas[start] - cost[start];

        while(start>end){
            if(tank<0){
                // start is not possible, in order to be able to reach start, 
                // we need to start earlier to get more gas in tank
                --start;
                tank += gas[start] - cost[start];
            }else{
                // this start is possible, wich means we can go further
                // let's extend end and see if we can go one more step
                ++end;
                tank += gas[end] - cost[end]
            }
        }
       
        // when start reaches end, if tank < 0; we don't find a way
        return tank<0? -1 : start;
    }
};
