## Phase 1: The Foundation (Complexity & Primitives)
Learn how to measure efficiency and use basic memory structures.

### Algorithmic Analysis
* **Time & Space Complexity:** Best, Average, and Worst-case scenarios.
* **Big O Notation:** Recognizing constant `O(1)`, linear `O(N)`, logarithmic `O(log N)`, linearithmic `O(N log N)`, quadratic `O(N^2)`.
* **Math Basics:** Logarithms, arithmetic series, and basic combinatorics.

### Linear Data Structures
* **Arrays & Strings:** Memory layout, dynamic resizing, and character encoding.
* **Linked Lists:** Singly, Doubly, and circular linked lists; using dummy nodes.
* **Stacks & Queues:** LIFO and FIFO principles, Circular Queues.

### Hashing
* **Hash Maps & Sets:** Key-value pairs, `O(1)` lookups.
* **Under the Hood:** Hash functions, collision resolution (chaining vs. open addressing).

---

## Phase 2: Core Algorithms & Non-Linear Structures
Transition from straight lines to trees, networks, and sorting logic.

### Recursion & Searching
* **Recursion:** Call stacks, base cases, and identifying recursive sub-problems.
* **Binary Search:** Standard search in `O(log N)` time.
* **Binary Search on Answer Space:** Using binary search to find an optimal maximum or minimum value.

### Sorting Algorithms
* **Basic Sorts:** Bubble, Selection, and Insertion Sort.
* **Divide & Conquer Sorts:** Merge Sort and Quick Sort.
* **Non-Comparison Sorts:** Counting Sort, Radix Sort, and Bucket Sort.

### Trees & Priority Queues
* **Binary Trees:** Traversals (Pre-order, In-order, Post-order, Level-order).
* **Binary Search Trees (BST):** Fast lookups and balanced tree concepts.
* **Heaps & Priority Queues:** Min-heaps, Max-heaps, and the Heapify process. 
* **Similar to Priority Queues:** **Deques** (Double-ended queues for dynamic sliding windows).



[Image of binary heap data structure]


### Graphs (Basics)
* **Representation:** Adjacency Matrices and Adjacency Lists.
* **Breadth-First Search (BFS):** Layer-by-layer exploration.
* **Depth-First Search (DFS):** Deep-path exploration and backtracking.

---

## Phase 3: Advanced Algorithmic Paradigms
This is the heavy-lifting phase where your newly added advanced concepts live. 

### Advanced Array, String & Stack Patterns
* **Two Pointers & Sliding Window:** Optimizing nested loops into `O(N)` linear passes.
* **Prefix Sum & Difference Arrays:** Pre-calculating arrays for instant range sum queries and range updates.
* **Monotonic Stack:** Finding the "Next Greater/Smaller Element" in `O(N)` time.
* **Similar Pattern:** **Monotonic Queue**, used strictly for finding the maximum/minimum in a sliding window in `O(N)` time.



### Range Query Data Structures
* **Segment Tree:** Lightning-fast `O(log N)` range queries (like sums or minimums) and single-element updates.
* **Similar Structure:** **Fenwick Tree (Binary Indexed Tree / BIT)**. Does the same thing as a Segment Tree for sums, but uses clever bitwise logic to use less memory and fewer lines of code.
* **Similar Structure:** **Sparse Table**. Used when the array never changes (immutable), allowing `O(1)` instant answers for range minimums.

### Advanced String Algorithms
* **Tries (Prefix Trees):** Highly efficient character-by-character storage for autocomplete and dictionaries.
* **Similar Algorithm:** **KMP (Knuth-Morris-Pratt)**. A pattern-matching algorithm that finds a substring inside a larger string in strictly `O(N + M)` time by skipping unnecessary comparisons.
* **Similar Algorithm:** **Rabin-Karp Algorithm**. Uses "rolling hashes" to find substrings efficiently.



### Advanced Graph Theory
* **Shortest Paths:** Dijkstra’s Algorithm (positive weights) and Bellman-Ford (handles negative weights).
* **Similar Algorithm:** **Floyd-Warshall Algorithm**. Finds the shortest path between *all* pairs of nodes in a graph.
* **Minimum Spanning Trees:** Kruskal’s (using Union-Find) and Prim’s algorithms.
* **Disjoint Set (Union-Find):** Network connectivity and cycle detection.
* **Topological Sorting:** Ordering dependencies (e.g., task scheduling).
* **Tarjan's Algorithm:** Finding Strongly Connected Components (SCCs), bridges, and articulation points in `O(V + E)` time.
* **Similar Algorithm:** **Kosaraju's Algorithm**. Another brilliantly simple way to find SCCs using two passes of DFS.



### Dynamic Programming & Advanced Logic
* **Dynamic Programming (DP):** Memoization (Top-Down), Tabulation (Bottom-Up), and classic problems like 0/1 Knapsack.
* **Advanced DP:** DP on Trees, Bitmask DP, and state machines.
* **Greedy Algorithms & Backtracking:** Interval scheduling, permutations, and puzzle solving.
* **Bit Manipulation:** XOR logic, bit masking, and shifting for hardware-level efficiency.

---

