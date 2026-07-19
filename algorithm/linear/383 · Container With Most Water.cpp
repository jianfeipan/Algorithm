class Solution {
public:
    /**
     * @param heights: a vector of integers
     * @return: an integer
     */

    //cleaner:

    int maxArea(vector<int>& heights) {
        int max_amount = 0;
        int left = 0;
        int right = heights.size()-1;
        while(left < right){
            const int current_area = (right - left)*min(heights[left], heights[right]);
            max_amount = max(max_amount, current_area);
            if(heights[left]<heights[right]){
                ++left;
            }else{
                --right;
            }
        }
        return max_amount;
    }

    
    int maxArea(vector<int> &heights) {
        /* 
            ides: use two pointers, one from left and another from right, the smaller one determin the volumn
            so from out side to inner, keep the bigger one and move the small one to center 

        */
        if(heights.size()<=1) return 0;

        int max = 0;

        int left = 0;
        int right = heights.size()-1;

        while(left < right)
        {
            //cout<<left<<"-"<<right<<endl;
            int h = 0;
            int l = right - left;
            if(heights[left] <= heights[right])
            {
                h = heights[left];
                ++left;
            }
            else
            {
                h = heights[right];
                --right;
            }

            const int surface = l*h;
            if(max < surface)
                max = surface;
        }

        return max;

    }
};
