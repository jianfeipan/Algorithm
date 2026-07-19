class Solution {
    
private:
    bool validNumber(int value)
    {
        return value<=255 && value >=0;
    }
    
    vector<list<int> > pareseToNumbers(const vector<int> & nums, int from, int numbersCount)
    {
        vector<list<int> > res;

        if(nums.size() - from == numbersCount)
        {
            list<int> onlyRes;
            for(int i =0; i<numbersCount; ++i)
            {
              onlyRes.push_back(nums[from+i]);
            }
            res.push_back(onlyRes);
        }
        else if(nums.size() - from > numbersCount)
        {   
            if ( nums.size() - from > numbersCount*3)
            {
                return res;
            }
            else
            {
                if(numbersCount == 1)
                {
                    if(nums[from]!=0 && nums.size() - from <=3)
                    {               
                        int num = 0;
                        for(int i =from; i<nums.size(); ++i)
                        {
                            num*=10;
                            num+=nums[i];
                        }
                        if(validNumber(num))
                        {
                            res.push_back({num});
                        }
                    }
                }
                else
                {  
                int first = nums[from];
                if(validNumber(first))
                {
                    vector<list<int> > nexts = pareseToNumbers(nums, from+1, numbersCount-1);
                    for(auto & next : nexts )
                    {
                        next.push_front(first);
                    }
                    
                    res.insert(res.end(), nexts.begin(), nexts.end());
                }
                
                if(nums[from]!=0)
                {
                    first = nums[from] *10 + nums[from+1];
                    if(validNumber(first))
                    {
                        vector<list<int> > nexts = pareseToNumbers(nums, from+2, numbersCount-1);
                        for(auto & next : nexts )
                        {
                            next.push_front(first);
                        }

                        res.insert(res.end(), nexts.begin(), nexts.end());
                    }
                    
                    first = nums[from] *100 + nums[from+1]*10 + nums[from+2];
                    if(validNumber(first))
                    {
                        vector<list<int> > nexts = pareseToNumbers(nums, from+3, numbersCount-1);
                        for(auto & next : nexts )
                        {
                            next.push_front(first);

                        }

                        res.insert(res.end(), nexts.begin(), nexts.end());
                        
                        
                    }
                }
                
            }
            }
            
        }
        return res;
    }
    
    
     bool isValid(string s) 
     {
        if (s[0] == '0' && s.size() == 1)
            return true;
        else if (s[0] == '0' && s.size() > 1)
            return false;
        else {
            int number = stoi(s);
            if (number > 0 && number < 256)
                return true;
        }
        return false;
    }
    
public:
    vector<string> restoreIpAddresses(string s) 
    {
        vector<int> nums(s.size(), 0);
        
        for(int i =0; i<s.size(); ++i)
        {
           nums[i] = (s[i]-'0');
        }
        
        vector<list<int> > res = pareseToNumbers(nums, 0, 4);
        
        vector<string> result;
        result.reserve(res.size());

        for(int i = 0; i<res.size(); ++i)
        {
            stringstream ss;
            int j = 0;
            for(int num : res[i])
            {
                ss<<num;
                //cout<< num<<endl;
                if(j!=3)
                {
                   ss <<'.';
                }
                j++;
            }
            ss.seekp(-1, std::ios_base::end);
            result.push_back(ss.str());
        }
        return result;
    }
    
    
        vector<string> restoreIpAddresses_withString(string s) {
            vector<vector<string>> result;
            int numberOfDots = 4;
            vector<string> current;
            helper(result, s, numberOfDots, 0, current);
            vector<string> ans;
            string temp = "";
            
            for (int i = 0; i < result.size(); i++) {
                for (int j = 0; j < result[i].size(); j++) {
                    temp += result[i][j];
                    temp += '.';
                    //cout<< temp << " ";
                }
                temp.pop_back();
                cout << temp << endl;
                ans.push_back(temp);
                temp = "";
                //cout<<endl;
            }

            return ans;
        }

        void helper(vector<vector<string>>& result, string& s, int numberOfDots, int start, vector<string>& current) {
            if (start > s.size())
                return;
            if (numberOfDots == 0 && start == s.size()) {
                result.push_back(current);
                return;
            }
            int n = s.size();
            if (n - start < numberOfDots || n - start > numberOfDots*3)
                return;
            string temp = "";
            for (int i = start; i < start + 3; i++) {
                temp += s[i];
                //cout << temp<<" ";
                if (isValid(temp)) {
                    current.push_back(temp);
                    helper(result, s, numberOfDots - 1, i + 1, current);
                    current.pop_back();
                }
            }
        }
};
