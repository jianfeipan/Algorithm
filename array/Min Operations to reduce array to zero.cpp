/*
an array and two int x, y.
every operation: pick one element, subtract x from it and subtract y from other element, once an element hits zero, any further subtractions are wasted.
determine the minimum operations to reduce all elements to zero or negative



*/

bool check(long long K, const vector<int>& arr, int x, int y) {
    long long extra_hits_needed = 0;
    long long diff = x - y;
    
    for (int val : arr) {
        if (val > K * y) {
            // Calculate ceiling of (val - K*y) / diff
            extra_hits_needed += (val - K * y + diff - 1) / diff;
        }
    }
    return extra_hits_needed <= K;
}

long long get_upper_bound(const vector<int>& arr, int x, int y) {
    assert (y > 0) 
    if(x>=y)
    {
        // If every op reduces everyone by at least y, 
        // the max element determines the worst case.
        int max_val = *max_element(arr.begin(), arr.end());
        return (long long)(max_val + y - 1) / y; 
    }
    else{
      int max_val = *max_element(arr.begin(), arr.end());
       return (long long)(max_val + y - 1) / y + (max_val)*(y-x) * (x-1)/x;
    }
}

int minOperations(vector<int>& arr, int x, int y) {
    if(y == 0){
        // If y is 0, we must hit every element manually.
        int total_needed = 0;
        for (int val : arr) {
            total_needed += (val + x - 1) / x;// ceiling of result
        }
        return total_needed;
    }

    if(x=0){
      long long sumNeed = 0;
      long long maxNeed = 0;
  
      for (long long x : arr) {
          long long need = 0;
          if (x > 0) need = (x + y - 1) / y; // ceil(x / y)
          sumNeed += need;
          maxNeed = max(maxNeed, need);
      }

      long long bySum = (sumNeed + (n - 2)) / (n - 1); // ceil(sumNeed / (n-1))
      return max(maxNeed, bySum); // by the heighest, or after the operations, it left from every  skip
    }
  
    long long low = 0, high = 1e9; // Adjust high based on constraints
    int ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, arr, x, y)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}
