#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <stdexcept>


class TopKSampler {
private:
   struct TokenLogit {
       int token_id;
       float logit;


       // Custom comparator for descending order
       bool operator>(const TokenLogit& other) const {
           return logit > other.logit;
       }
   };


   // Thread-local random engine for high-concurrency inference environments
   mutable std::mt19934 rng_;


public:
   TopKSampler() {
       std::random_device rd;
       rng_.seed(rd());
   }


   /**
    * Samples a token from raw logits using Top-K filtering.
    * @param logits Raw unnormalized outputs from the model (size = Vocab Size).
    * @param k The number of top tokens to keep.
    * @param temperature Sampling temperature (lower = more deterministic).
    * @return Selected token ID.
    */
   int sample(const std::vector<float>& logits, int k, float temperature = 1.0f) const {
       if (logits.empty()) {
           throw std::invalid_argument("Logits vector cannot be empty.");
       }


       // Handle edge case where K is larger than the vocabulary
       size_t vocab_size = logits.size();
       k = std::min(k, static_cast<int>(vocab_size));
       k = std::max(k, 1); // K must be at least 1


       // 1. Pack logits with their original token IDs
       std::vector<TokenLogit> token_logits(vocab_size);
       for (size_t i = 0; i < vocab_size; ++i) {
           token_logits[i] = { static_cast<int>(i), logits[i] };
       }


       // 2. O(V) Quickselect: Move top K elements to the front
       std::nth_element(token_logits.begin(),
                        token_logits.begin() + k,
                        token_logits.end(),
                        std::greater<TokenLogit>());


       // 3. O(K log K) Sort: Sort only the top K elements
       std::sort(token_logits.begin(), token_logits.begin() + k, std::greater<TokenLogit>());


       // 4. Apply Temperature Scaling and Compute Softmax over Top-K elements
       std::vector<float> probabilities(k);
       float max_logit = token_logits[0].logit; // For numerical stability
       float sum_exp = 0.0f;


       // Ensure temperature isn't zero to avoid division by zero
       float inv_temp = (temperature < 1e-5f) ? 1.0f : (1.0f / temperature);


       for (int i = 0; i < k; ++i) {
           // Subtract max_logit to prevent overflow during exp()
           float exp_val = std::exp((token_logits[i].logit - max_logit) * inv_temp);
           probabilities[i] = exp_val;
           sum_exp += exp_val;
       }


       // Normalize probabilities
       for (int i = 0; i < k; ++i) {
           probabilities[i] /= sum_exp;
       }


       // 5. Categorical Sampling (Roulette Wheel Selection)
       if (temperature < 1e-5f) {
           // Argmax shortcut if temperature is basically 0 (Greedy Decoding)
           return token_logits[0].token_id;
       }


       std::uniform_real_distribution<float> dist(0.0f, 1.0f);
       float r = dist(rng_);
       float cumulative_prob = 0.0f;


       for (int i = 0; i < k; ++i) {
           cumulative_prob += probabilities[i];
           if (r <= cumulative_prob) {
               return token_logits[i].token_id;
           }
       }


       // Fallback due to floating-point rounding anomalies
       return token_logits[k - 1].token_id;
   }
};




/*
Using a **Min-Heap** (specifically via `std::priority_queue` or `std::make_heap` in C++) is actually a very classic textbook approach for finding the top $K$ elements.


However, in the context of **high-performance AI inference modules**, a Min-Heap is usually rejected because it is fundamentally **slower and less CPU-cache-friendly** than `std::nth_element` (Quickselect).


Here is a breakdown of why a Min-Heap loses out in production environments.


---


## 1. Algorithmic Complexity: $O(V \log K)$ vs. $O(V)$


Let $V$ be the vocabulary size (e.g., 128,000) and $K$ be the sampling size (e.g., 50).


* **Min-Heap Approach**: You iterate through all $V$ elements. For each element, you push it into the heap. If the heap size exceeds $K$, you pop the minimum element. Pushing and popping takes $O(\log K)$ time.
* **Total Time Complexity:** $O(V \log K)$




* **`std::nth_element` Approach**: This uses a selection algorithm (Quickselect) that partitions the array around a pivot. It does *not* sort the entire array, nor does it maintain a tree structure as it goes.
* **Total Time Complexity:** Strict average **$O(V)$**






While $\log(50)$ is small ($\approx 5.6$), multiplying it by $128,000$ tokens means a Min-Heap performs roughly **700,000 pointer/index manipulations and structural swaps**, whereas Quickselect performs linear scans.


---


## 2. Memory Layout and Cache Trashing


This is the biggest hidden killer in hardware execution.


A Min-Heap requires constant element swapping to maintain the heap invariant (parent node $\le$ child nodes).


* Every time a new larger logit is found, it is pushed to the bottom of the heap and must "bubble up", swapping places with elements across the heap array.
* These non-linear memory swaps prevent the CPU from predicting memory access patterns, causing frequent **CPU cache line invalidations**.


Conversely, `std::nth_element` runs mostly linear, localized memory partitions. The CPU’s hardware prefetcher can easily predict the next memory address, leading to a much higher **CPU Cache Hit Rate**.


---


## 3. The Math: When Does Min-Heap Win?


A Min-Heap is only superior when the data is a **streaming API**—meaning you receive the 128,000 tokens one-by-one over a network, and you cannot fit them all in memory at once.


But in AI inference, the entire logit tensor is outputted by the GPU/CPU matrix multiplication **all at once into a contiguous memory block**. Since the data is already fully present in memory, running an in-place $O(V)$ linear scan is always faster.


---


## Summary Comparison


| Metric | Min-Heap (`std::priority_queue`) | Quickselect (`std::nth_element`) |
| --- | --- | --- |
| **Time Complexity** | $O(V \log K)$ | **$O(V)$ average** |
| **Memory Overheads** | High (constant state swapping) | **Minimal (in-place partitioning)** |
| **CPU Cache Efficiency** | Poor (pointer-chasing tree logic) | **Excellent (linear array scanning)** |
| **Best Used For** | Streaming data streams | **Batch-allocated arrays (LLM Logits)** |


In modern inference frameworks like Hugging Face `transformers` (Python/C++ backends), `llama.cpp`, or vLLM, you will almost exclusively see partitioning/sorting strategies rather than Heap allocations for Top-$K$ layers.
*/

