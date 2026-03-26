pair<int,int> binarySearch(vector<int>& arr, int target) {
    int l = 0, r = (int)arr.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;     // avoid overflow vs (l+r)/2
        if (arr[m] == target)
            return {m, m};            // exact match
        else if (arr[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }
    // No exact match. Now r < l, and r == l - 1.
    // r = index of largest element < target  (-1 if none)
    // l = index of smallest element > target (n if none)
    //     (cannot be == target, since that returns {m,m} above)
    return {r, l};
}

/*
Key insight: use while(l <= r) with l=m+1, r=m-1.
After the loop, r = l-1. The target would sit between arr[r] and arr[l].
  - r is the last element < target  (left neighbor, could be -1 if target < all)
  - l is the first element >= target (right neighbor, could be n if target > all)
*/
