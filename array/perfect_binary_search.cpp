int binarySearch(vector<int>& arr, int target) {
    int l = -1, r = (int)arr.size();
    
    while (l+1!=r) {
        int m = l + (r - l) / 2;     // avoid overflow vs (l+r)/2
        if (arr[m] < target) // IS_BLUE:   BLUE l | r RED
            l = m;
        else
            r = m ;
    }
    return l or r;
}


std::lower_bound: IS_BLUE(< target) return r : first element >= target
std::upper_bound: IS_BLUE(<= target) return r: first element > target 


/*
Key insight: use while(l <= r) with l=m+1, r=m-1.
After the loop, r = l-1. The target would sit between arr[r] and arr[l].
  - r is the last element < target  (left neighbor, could be -1 if target < all)
  - l is the first element >= target (right neighbor, could be n if target > all)
*/
