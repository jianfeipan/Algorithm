class Solution {//O(N^k)
public:
    int getLengthOfOptimalCompression(string s, int k) 
    {
        return getLengthOfOptimalCompression(s, k ,0);
    }

    
    int getLengthOfOptimalCompression(string s, int k, int from) 
    {   
        //cout<<s<<k<<endl;
        if(cache[s][k] !=0) return cache[s][k];
        
        if(k == 0 )
        {
            cache[s][k] = compressionLen(s);
            return cache[s][k];
        }
        
        int minLen = INT_MAX;
        
        for(size_t i = from ; i<s.size(); ++i)//O(N^k)
        {
            string next = s;
            next.erase(next.begin() + i);
            minLen = min(minLen, getLengthOfOptimalCompression(next, k-1, i));
        }
        cache[s][k] = minLen;
        return minLen;
    }
    
private:
    int compressionLen(const string & s)
    {
        if(s.empty()) return 0;
        
        char current = s[0];
        int count = 1;
        
        string compressed;
        for(size_t i =1; i<s.size(); ++i)
        {
            if(s[i] == current)
            {
                count++;
            }
            else
            {
                compressed+=current;
                if(count!=1) compressed+=to_string(count);
                
                current = s[i];
                count = 1;
            }
        }
        
        compressed+=current;
        if(count!=1) compressed+=to_string(count);
        
        //cout<< s << ":"<<compressed.size()<<endl;
        
        return compressed.size();
    }
private:
    unordered_map<string, unordered_map<int, int>> cache;
    
};
