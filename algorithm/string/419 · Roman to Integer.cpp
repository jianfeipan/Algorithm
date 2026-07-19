class Solution {
public:
    /**
     * @param s: Roman representation
     * @return: an integer
     */
    int romanToInt(string &s) {

        if(s.empty()) return 0;

        const map<char, int> values({
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        });

        /*
        idea : from left to right, with  a buffer, [a b c d...]
        if(a == b) add
        elif a> b add to sum and start new buffer
        elif a<b buffer is a minus
        */

        int sum = 0;
        char current = s[0];
        int currentLevel = values.at(current);

        for(size_t i = 1; i<s.size(); ++i)
        {
            if(values.at(s[i]) == values.at(current)) 
            {
                currentLevel+=values.at(current);
            }
            else
            { 
                if(values.at(s[i]) < values.at(current))
                {
                    sum+= currentLevel;
                }
                else
                {
                    sum-=currentLevel;
                }
                current = s[i];
                currentLevel = values.at(current);
            }
        }

        sum+=currentLevel;

        return sum;

    }

};
