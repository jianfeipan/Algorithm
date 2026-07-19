class Solution {
public:
    /**
     * @param citations: a list of integers
     * @return: return a integer
     */
    int hIndex(vector<int> &citations) {
        // N papaer each cititions>=N
        std::sort(citations.begin(), citations.end(),[](int left, int right){
            return left>right;
        });

        int hIndex = 0;
        for(int i = 0; i<citations.size();i++)
        {
            if(citations[i] >=i+1)// pay attention to this condition, we are compare if first citation is once, so the citation  = i+1 
            {
                hIndex = i+1;
            }
            else
            {
                break;
            }
        }
        return hIndex;
    }
};
