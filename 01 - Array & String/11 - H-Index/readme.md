
# H-Index

## Problem Statement
Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their $i$-th paper, return the researcher's **h-index**.

According to the definition of h-index on Wikipedia: A scientist has an index $h$ if $h$ of their $n$ papers have at least $h$ citations each, and the other $n - h$ papers have no more than $h$ citations each.

If there are multiple possible values for $h$, the **maximum** one is taken as the h-index.

### What the problem actually wants:
You need to find a maximum threshold number $h$ such that there are at least $h$ papers in the array that have a citation count greater than or equal to $h$. 

* **Example:** `citations = [3, 0, 6, 1, 5]`
  * If we choose $h = 3$, there are 3 papers with at least 3 citations (`3`, `6`, and `5`). The remaining papers (`0` and `1`) have fewer than 3 citations. 
  * Thus, the output is `3`.

**Problem Link:** [LeetCode - H-Index](https://leetcode.com/problems/h-index/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Approach 1: Optimized Solution (Sorting)

### Source Code
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        
        // Sort the citations in descending order
        sort(citations.begin(), citations.end(), greater<int>());

        for(int i = 0; i < n; i++){
            // If the current citation count is less than the number of papers counted so far
            if(citations[i] < i + 1) return i;
        }

        return n;
    }
};

```

### Code Explanation

1. **Sorting:** We sort the `citations` array in descending order (largest to smallest). This groups the most-cited papers at the beginning of the array.
2. **Linear Scan:** We iterate through the sorted array using index `i`. The value `i + 1` represents the number of papers tracked so far (since indices are 0-based).
3. **Break Condition:** Because the array is sorted, as long as `citations[i] >= i + 1`, it means we have found at least `i + 1` papers with a citation count of at least `i + 1`. The moment a paper's citation count drops below this value (`citations[i] < i + 1`), we can no longer maintain a valid h-index including this paper. Since we are looking for the maximum threshold, the valid count up to the previous paper (`i`) is returned immediately.
4. **Fallback:** If all papers satisfy the condition, the h-index is the total number of papers `n`.

### Dry Run / Iteration Example

Let's trace the execution with **`citations = [3, 0, 6, 1, 5]`** (Total papers $n = 5$).

* **Step 1:** Sort descending $\rightarrow$ `citations = [6, 5, 3, 1, 0]`

| Index (`i`) | Citation Count (`citations[i]`) | Target Count (`i + 1`) | Condition Checked (`citations[i] < i + 1`) | Action |
| --- | --- | --- | --- | --- |
| **0** | 6 | 1 | 6 < 1 (False) | Continue loop |
| **1** | 5 | 2 | 5 < 2 (False) | Continue loop |
| **2** | 3 | 3 | 3 < 3 (False) | Continue loop |
| **3** | 1 | 4 | 1 < 4 (**True**) | **Stop & Return `i` (which is 3)** |

**Final Output Returned:** `3`

### Complexity Analysis

* **Time Complexity:** $O(n \log n)$ due to the sorting step. The subsequent linear loop takes $O(n)$ time, making the overall time complexity dominated by the sort algorithm.
* **Space Complexity:** $O(1)$ auxiliary space if we sort in-place (or $O(\log n)$ depending on the underlying implementation of `std::sort` for the recursive call stack).

---

## Approach 2: Secondary Solution (Brute-Force Linear Search)

### Source Code

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();

        for(int h = 1; h <= n; h++){
            int cites = 0;
            for(int j = 0; j < n; j++){
                if(citations[j] >= h) cites++;
            }

            if(cites < h) return h - 1;
        }

        return n;
    }
};

```

### Code Explanation

1. **Outer Loop (`h` from 1 to `n`):** Tests every possible h-index value sequentially up to the total number of published papers.
2. **Inner Loop (`j` from 0 to `n-1`):** Traverses the entire unsorted array to count how many papers have at least `h` citations.
3. **Condition Check:** If the tracked number of papers (`cites`) drops below the evaluated benchmark `h`, it implies an h-index of `h` is impossible. The maximum achievable valid h-index up to this failure is returned as `h - 1`.

### Dry Run / Iteration Example

Let's trace the execution with **`citations = [3, 0, 6, 1, 5]`** ($n = 5$).

| Iteration (`h`) | Paper Citations Checked (`citations[j] >= h`) | Count (`cites`) | Condition Checked (`cites < h`) | Action |
| --- | --- | --- | --- | --- |
| **h = 1** | 3 $\ge$ 1, 0 $\ge$ 1, 6 $\ge$ 1, 1 $\ge$ 1, 5 $\ge$ 1 | **4** | 4 < 1 (False) | Continue loop |
| **h = 2** | 3 $\ge$ 2, 0 $\ge$ 2, 6 $\ge$ 2, 1 $\ge$ 2, 5 $\ge$ 2 | **3** | 3 < 2 (False) | Continue loop |
| **h = 3** | 3 $\ge$ 3, 0 $\ge$ 3, 6 $\ge$ 3, 1 $\ge$ 3, 5 $\ge$ 3 | **3** | 3 < 3 (False) | Continue loop |
| **h = 4** | 3 $\ge$ 4, 0 $\ge$ 4, 6 $\ge$ 4, 1 $\ge$ 4, 5 $\ge$ 4 | **2** | 2 < 4 (**True**) | **Stop & Return `h - 1` (4 - 1 = 3)** |

**Final Output Returned:** `3`

### Complexity Analysis

* **Time Complexity:** 
$$O(n^2)$$


 because for every possible value of $h$ (up to $n$ values), the inner loop scans the entire array of size $n$.
* **Space Complexity:** $O(1)$ as it runs entirely in place using fixed scalar loop variables.

