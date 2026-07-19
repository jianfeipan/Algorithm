class Solution {
public:
    /**
     * @param str: str: the given string
     * @return: char: the first unique character in a given string
     */
    char firstUniqChar(string &str) {
        map<char, size_t> count;

        for(char c : str)
        {
            ++count[c];
        }

        for(char c : str)
        {
            if(count[c]==1)
                return c;
        }

        throw new std::invalid_argument("no unique char");
        return 0;
    }
};
