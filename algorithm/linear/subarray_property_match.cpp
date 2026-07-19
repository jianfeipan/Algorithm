#include <iostream>
#include <vector>
#include <unordered_map>
/*
find the number of subarrays satisfied: 

arr[i] == arr[j] == sum(arr[i+1: j-1])


given an array of length 10^5
find the number of subarrays satisfied: 
arr[i] == arr[j] == sum(arr[i+1: j-1])
Prefix Sum S[N+1]: S[i] means the sum to i-1 S[0]=0
let j > i
and we have  sum(arr[i+1: j-1]) = S[j] - S[i+1] = S[j] - (S[i] + arr[i]) = arr[i] = arr[j]
so we have two condition
arr[i] = arr[j]
S[i]   = Sj - 2*arr[j]
// the object here is to put i and j in two sides
// and we have j>i. so we can do one pass from left to right, compute j and looking for i, 
Hash map -> key_value paire [arr[i], S[i]], then use the current index as j try to find int the map



*/
using namespace std;

// Custom hash function for pair to use in unordered_map
struct pair_hash {
    inline size_t operator()(const pair<long long, long long> & v) const {
        return v.first * 31 + v.second;
    }
};

long long solve() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    // Key: {element_value, prefix_sum_up_to_that_element}
    // Value: count of occurrences
    unordered_map<pair<long long, long long>, int, pair_hash> seen;
    
    long long prefix_sum = 0;
    long long count = 0;

    for (int j = 0; j < n; j++) {
        // Target S[i] must equal S[j] - 2 * arr[j]
        // And arr[i] must equal arr[j]
        long long target_S_i = prefix_sum + arr[j] - 2 * arr[j]; 
        // Note: prefix_sum here is S[j]. 
        // S[j] = S[j-1] + arr[j-1]. Let's keep it clean:
        
        // At this point in the loop, 'prefix_sum' represents S[j]
        long long current_S_j = prefix_sum;
        long long target_S_i_final = current_S_j - 2 * arr[j];
        
        pair<long long, long long> target = {arr[j], target_S_i_final};
        
        if (seen.count(target)) {
            count += seen[target];
        }

        // Add the current element into the map for future j's
        // We store {arr[i], S[i]}
        seen[{arr[j], current_S_j}]++;
        
        // Update prefix sum for the next iteration (S[j+1])
        prefix_sum += arr[j];
    }

    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << solve() << endl;
    return 0;
}
