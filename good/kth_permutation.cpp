#include <vector>
#include <iostream>
#include <vector>
#include <numeric>   // for std::iota
#include <algorithm> // for std::next_permutation
/*
given number n, k: 
    0 1 2 3 ... n-1
    kth permutation (k start from 0)

*/

// all permutations in lexi order:
std::vector<std::vector<int>> getPermutations(int n) {
    if (n <= 0) return {};
    
    // 1. Initialize vector with {0, 1, 2, ..., n-1}
    std::vector<int> nums(n);
    std::iota(nums.begin(), nums.end(), 0);
    
    // 2. Push each permutation into the result matrix
    std::vector<std::vector<int>> result;
    do {
        result.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));
    //next lexicographically greater arrangement
    return result;
}

template <typename BidiIter>
bool clean_next_permutation(BidiIter first, BidiIter last) {
    if (first == last) return false; 
    
    BidiIter pivot_candidate = last;
    --pivot_candidate; // move to last element
    if (first == pivot_candidate) return false; // Single element range

    //  [1, 5, 8, 4, 7, 6, 5, 3, 1]

    while (true) {
        BidiIter right_neighbor = pivot_candidate;
        
        --pivot_candidate; 
        if (*pivot_candidate < *right_neighbor) {
            //            v
            //  [1, 5, 8, 4, 7, 6, 5, 3, 1]
            // Step 3: Find the successor (first element from right greater than pivot)
            BidiIter successor = last;
            do {
                --successor;
            } while (*pivot_candidate >= *successor);
            //            v        s
            //  [1, 5, 8, 4, 7, 6, 5, 3, 1]

            std::iter_swap(pivot_candidate, successor);
            //            v        s
            //  [1, 5, 8, 5, 7, 6, 4, 3, 1]
            //            |        |
            //Reverse the suffix to get the smallest lexicographical arrangement
            std::reverse(right_neighbor, last);
            //            v        s
            //  [1, 5, 8, 5, 7, 6, 4, 1, 3]
            //                        ----
            return true; 
        }
        
        if (pivot_candidate == first) { // already the last one [5 4 3 2 1]
            std::reverse(first, last); // [1 2 3 4 5]
            return false;
        }
    }
}

std::vector<int> kth_permutation(int n, int k_) {
    /*
    n = 4: [0 1 2 3], all permutations: 4! = 24 , k = 14 for exmaple
    start with 0: [0, x x x]: has 3! = 6 permutaions index 0 ~ 5 (0*3! ~ 1*3!-1)
    start with 1: [1, x x x]: has 3! = 6 permutaions index 6 ~ 11 (3! ~ 2*3! - 1)
    start with 2: [2, x x x]: has 3! = 6 permutaions index 12 ~17 (2*3! ~ 3*3! - 1)
    start with 3: [3, x x x]: has 3! = 6 permutaions index 18 ~23 (3*3! ~ 4*3! - 1)
    
    index    0 1 2 3
    factors  1 1 2 6

    k = 14: first index means where does 14 fall in the ranges size of 3!
        14/3! = 2  -> 2 element in [0 1 2 3] -> 2

        so the permutaions is [2, x x x]

        then what's left in the order permutation of [0 1 3] (we get this from erasing 2 from nums)
        and the rank in this permutaions list is k%3! = 2

    next iteration: k =2
        means we need the index 2 of the permutation in [0 1 3]
        2 / 2! = 1 -> 1 element in [0  1 3] -> 1

        so the permutation is [1, x x]

        next k%2! = 0 element in [0, 3] -> 0
        next k/1 = 0 element in [3] -> 3

    */
    std::vector<int> numbers(n, 0);
    std::iota(numbers.begin(), numbers.end(), 0);
    // preompute 1! 2! ... (n-1)!
    long long k = k_;
    std::vector<long long> factors(n, 1);
    for (int i = 1; i < n; i++) {
        factors[i] = factors[i-1] * i; // Precomputes (n-1)!
    }

    std::vector<int> result;
    result.reserve(n); // Pre-allocate memory for performance
    
    // 2. Select digits using Factorial Number System
    for (int i = n; i > 0; i--) {
        int index = k / factors[i-1];
        
        result.push_back(numbers[index]);
        
        // Remove the selected number from the pool
        numbers.erase(numbers.begin() + index);
        
        // Update k and the factorial factor for the next iteration
        k %= factors[i-1];
    }
    return result;
}

int main() {
    int n = 4;
    int k = 14; // 0-based index

    std::vector<int> kthPerm = kth_permutation(n, k);

    std::cout << "The " << k << "-th permutation (0-based) for n=" << n << " is: ";
    for (int x : kthPerm) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
