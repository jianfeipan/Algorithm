class Solution {
public:
    int compress(vector<char>& chars) 
    {
        int compressed = 0;
        int current = 0;

        while(current<chars.size())
        {
            const int start = current;
            
            while(current<chars.size() && chars[start] == chars[current]) current++;
            
            chars[compressed++] = chars[start];
            
            int number = current-start;
            if(number>1)
            {
                string numStr = to_string(number);
                for (char ch : cnt){
                    chars[compressed++] = ch;
                }
            }            
        }
        
        return compressed;
        
    }
};
