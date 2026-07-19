class Solution {

/*

Description
Implement a method to perform basic string compression using the counts of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3.

If the "compressed" string would not become smaller than the original string, your method should return the original string.

You can assume the string has only upper and lower case letters (a-z).

Example
Example 1:

Input: str = "aabcccccaaa"
Output: "a2b1c5a3"
Example 2:

Input: str = "aabbcc"
Output: "aabbcc"

*/
public:
    /**
     * @param originalString: a string
     * @return: a compressed string
     */
    string compress(string &originalString) {
        if(originalString.empty()) return originalString;

        string result;
        
        char current = originalString[0];
        size_t count = 1;
        result+=current;
        for(int index = 1; index < originalString.size(); ++index)
        {
            if(originalString[index] == current)
            {
                ++count;
            }
            else
            {
                result+=to_string(count);
                current = originalString[index];
                result+=current;
                count = 1;
            }
        }
        result+=to_string(count);

        return originalString.size()>result.size() ? result : originalString;

    }
};
