class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // median means: number on left is same on the right 
        if (nums2.size() < nums1.size()) {
            swap(nums1, nums2);
        }
        nums1.insert(nums1.begin(), INT_MIN);
        nums1.push_back(INT_MAX);
        nums2.insert(nums2.begin(), INT_MIN);
        nums2.push_back(INT_MAX);

        const auto& n = nums1.size();
        const auto& m = nums2.size();

        auto isMedian = [&](int m1, int m2){
        /*     m1
             1 3 ] 5 7
             m2 
             2 ] 4 
        */
            return (nums1[m1] <= nums2[m2+1])
                && (nums2[m2] <= nums1[m1+1]);
        };  

        int l = -1;
        int r = n;  
        while(l+1 != r){
            auto m1 = l + (r - l)/2;
            auto m2 = (m+n)/2 - m1 - 2; 
            // we need (m+n)/2 element on left of m1], m2], m1] has m1+1 elements
            // (m+n)/2 = m1+1 + m2+1
            if(isMedian(m1, m2)){ l = m1; break; }
            else{
                if(nums1[m1] > nums2[m2]) r=m1; // num1[m1] too big, we need to search m1's left
                else l=m1;
            }
            
        }

        int m1 = l;
        int m2 = (m+n)/2 - m1 - 2;
        cout<<m1 << "-"<<m2<<endl;
        double median = 0.;
        if((m+n)%2 == 0){
        /*     m1
             1 3 | 5 7
             m2 
             2 | 4 

               m1
             1 2 | 
              m2 
                |3  4 
        
        */
            median = (max(nums1[m1], nums2[m2]) + min(nums1[m1+1], nums2[m2+1]))/2.0;
        }else{
        /*   m1
             1 | 3 5 
             m2 
             2 | 4 
            n = 3, m=2 m+n = 5 (m+n)/2 = 2
            m1 = 0
            m2 = 2 - m1 -2 = 0
        */
            median = min(nums1[m1+1], nums2[m2+1]);
        }

        return median;


    }
};
