class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) 
    {
        int n = arr.size();
        int count = 1;
        int from = 0;
        
        for (int i = 1; i < n; ++i) 
        {
           
            if (arr[i-1] == arr[i]) 
            {
                from = i;
            } 
            else 
            {
                if(i == n-1
                    ||arr[i-1] < arr[i] && arr[i] <= arr[i+1] 
                    || arr[i-1] > arr[i] && arr[i] >= arr[i+1])
                {
                    count = max(count, i - from + 1);
                    from = i;
                }
              
            }
        }
        

        return count;
        
    }
};
